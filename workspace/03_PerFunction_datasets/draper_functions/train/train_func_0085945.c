HashTable_getValue(HashTable * table, String * key)
{
	List * currentList;
	KeyValuePair * tmpPair;
	void * data;

	if(table == NULL || key == NULL)
		return NULL;

	tmpPair = KeyValuePair_create(key);
	currentList = table->table[hash(key, table->size)];

	data = List_getMatchedData(currentList, tmpPair, KeyValuePair_isEqual);
	KeyValuePair_destroy(tmpPair);

	return KeyValuePair_getValue(data);
}
