itemAtKey(unsigned char key) {
	map<unsigned char, Item>::iterator i = _items.find(key);
	if (i != _items.end())
		return i->second;
	return NO_ITEM;
}
