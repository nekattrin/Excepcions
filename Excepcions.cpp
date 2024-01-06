//Разработать набор классов(минимум 5 классов) по предметной
//области «Магазин электроники».Функционал программы должен
//позволить собрать данные о заказе.Сгенерировать минимум пять типов
//исключительных ситуаций.Реализовать перенаправление исключительных
//ситуаций.Сгенерировать минимум одну исключительную ситуацию с
//оператором new.Создать исключительную ситуацию в конструкторе и
//продемонстрировать вызов конструкторов и деструкторов.Задать
//собственную функцию завершения.Создать собственный(пользовательский)
//класс исключения, сгенерировать исключение этого типа и обработать его.


#include <iostream>
#include <iomanip>

using namespace std;


class Item {
protected:
	string name;
	int price;
public:
	Item(string name = "X", int price = 0) { this->name = name; this->price = price; }
	//void busketAdd();
	//void showData();
	friend class Shop;
	friend class Order;
	//~Item() { cout << setw(20) << "Item died\n"; }
};
static Item X;
class Shop {
	string ShopName;


public:
	//~Shop() { cout << setw(20) << "Shop died\n"; };
	Shop(string name) {
		if (name == "1") throw 1;
		this->ShopName = name;
	};
	void showData() { cout << setw(20) << this->ShopName; };
	Item itemList[5];
	void showItem(int i) { cout << i + 1 << "." << itemList[i].name << setw(16 - size(itemList[i].name)) << itemList[i].price << " deneg" << endl; }
};

class OrderStatus {
protected:
	string payment;
public:
	OrderStatus() { payment = "not payed"; }
	//void pay();
	//~OrderStatus() { cout << setw(20) << "OrderStatus died\n"; };
};

class Order : public Item, public OrderStatus {
	int number;
public:
	friend class Shop;
	friend class Item;
	Order(Item item = X, int number = 0) { this->name = item.name; this->price = item.price;  this->number = number + 1; }
	void showOrder();
	//~Order() { cout << setw(20) << "Order died\n"; };
	/*Order operator =(const Order& order) {

		this->name = order.name;
		this->number = order.number;
		this->payment = order.payment;
		this->price = order.price;
	};*/
};


void Order::showOrder()
{

	cout << this->number << " - " << this->name << setw(16 - size(this->name)) << this->price << setw(10) << this->payment;
}

class Busket {

	int numOrders = 0;
	static const int MAX_ORDERS = 10;
public:
	Order* OrderList[];
	Busket() {
		*OrderList = new Order[MAX_ORDERS];
	}

	void showBusket();
	friend Order;

	void addOrder(Order* o) {
		OrderList[numOrders++] = o;
	}
	//int getSum();
	~Busket() {
		for (int i = 0; i < numOrders; i++) {
			delete OrderList[i];
		}
		delete[] OrderList;
		cout << setw(20) << "Busket died\n";
	}
};

void Busket::showBusket() {
	cout << "Your busket:" << endl;

	try {
		for (int i = 0; i < numOrders; i++) {
			if (this->OrderList[i] == NULL) throw "Finalboss";
			if (i == 2)throw runtime_error("runtime_error");
			this->OrderList[i]->showOrder();
			//Order order = *this->OrderList[i];

			//order.showOrder();
			cout << endl;
		}


	}

	catch (runtime_error err) {
		cout << err.what() << endl;
		throw;
	}
}

void termFunc() {
	cout << " termFunc() called by terminate().\n";
	// операторы освобождения ресурсов
	exit(-1);
}


int main() {

	set_terminate(termFunc);
	bad_alloc exept;

	cout << "You entered the electronics store 'Lemon'" << endl << endl;
	//Shop shop1("Apple");
	Shop shop("Lemon");

	/*Item item11("Iphone", 1000);
	Item item12("AppleWatch", 150);
	Item item13("IPad", 900);
	Item item14("MacBook", 1200);
	Item item15("AirPods", 200);*/

	/*shop1.itemList[0] = item11;
	shop1.itemList[1] = item12;
	shop1.itemList[2] = item13;
	shop1.itemList[3] = item14;
	shop1.itemList[4] = item15;*/


	Item item1("Lphone", 1000);
	Item item2("LemonWatch", 150);
	Item item3("LPad", 900);
	Item item4("MagBook", 1200);
	Item item5("WonderPods", 200);

	shop.itemList[0] = item1;
	shop.itemList[1] = item2;
	shop.itemList[2] = item3;
	shop.itemList[3] = item4;
	shop.itemList[4] = item5;


	//shop.showData(); 
	/*cout << endl << endl << "Enter 1 to go to the left" << endl << "enter 2 to go to the right" << endl;
	int shopChoise;
	cin >> shopChoise;*/
	//cout << endl;
	//if (shopChoise == 1) ///// exception
	//{
	//	for (int i = 0; i < 5; i++)
	//		 shop1.showItem(i);	
	//}
	//else
	//{
	//	for (int i = 0; i < 5; i++)
	//		shop.showItem(i);
	//}

	for (int i = 0; i < 5; i++)
		shop.showItem(i);

	Busket busket;
	int orderNumber = 0;

	do {
		try {
			cout << "choose item: ";
			int itemChoise;
			cin >> itemChoise;
			if (itemChoise > 5) throw false;
			Order order(shop.itemList[itemChoise - 1], orderNumber);
			Order* newOrder = new Order();

			if (!(newOrder = new Order()))
				throw exept;
			*newOrder = order;
			busket.addOrder(newOrder);
			orderNumber++;
			busket.showBusket();
		}
		catch (bool) {
			cout << "There is no such item\n";
		}
		catch (bad_alloc exept) {

			cout << exept.what() << endl;
		}
		catch (string) {
			"Final";

		}
		catch (...) {
			cout << "Absolute Handler" << endl;
			break;
		}


	} while (true);

	cout << "Cycle Complete" << endl;
	try {
		Shop shop1("1");
	}



	catch (int) {
		cout << "constructor handler" << endl;
	}
	try {
		int i = 1;
		Shop shop2("2");
		if (i) throw shop2;
	}

	catch (int) {
		cout << "constructor handler" << endl;
	}

}




