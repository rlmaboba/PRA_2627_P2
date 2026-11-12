#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2627_P1/ListLinked.h"

template <typename V>

class HashTable: public Dict<V>{
	private:
		int n;
		int max;
		ListLinked<TableEntry<V>>*table;
		int h(std::string key){
			int sum = 0;
			for(size_t i = 0; i < key.length(); i++){
				sum += static_cast<unsigned char>(key.at(i));
			}
			return sum % max;
		}
	public:
		HashTable(int size){
			n = 0;
			max = size;
			table = new ListLinked<TableEntry<V>>[max];
		}
		~HashTable(){
			delete [] table;
		}
		int capacity(){
			return max;
		}
		V operator[](std::string key){
			return search(key);
		}
		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			out << "HashTable [entradas: " << th.n << ", capacidad: " << th.max << "]" << std::endl;
			for(int i = 0; i < th.max; i++){
				out << "Cubeta " << i << ": " << std::endl;
				out << "List: " << th.table[i];
			}
			return out;
		}
		void insert(std::string key, V value) override{
			int pos = h(key);
			TableEntry<V> entry(key,value);
			if(table[pos].search(entry) != -1){
				throw std::runtime_error("La clave '" + key + "' ya existe en la tabla hash");
			}
			table[pos].prepend(entry);
			n++;
		}
		V search(std::string key) override{
			int i = h(key);
			TableEntry<V> entry(key);
			int pos = table[i].search(entry);
			if(pos != -1){
				return table[i].get(pos).value;
			}
			throw std::runtime_error("Clave '" + key + "' no encontrada en la tabla");
		}
		V remove(std::string key) override{
			int i = h(key);
			TableEntry<V> entry(key);
			int pos = table[i].search(entry);
			if(pos != -1){
				V val = table[i].get(pos).value;
				table[i].remove(pos);
				n--;
				return val;
			}
			throw std::runtime_error("Clave '" + key + "' no encontrada en la tabla");
		}
		int entries() override{
			return n;
		}
};
#endif
