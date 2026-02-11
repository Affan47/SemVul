Reserve(int newCapacity)
{
  if(newCapacity <= _capacity)
    return;


  unsigned char *p = new unsigned char[newCapacity * _itemSize];
  int numRecordsToMove = _capacity;
  memmove(p, _items, _itemSize * numRecordsToMove);
  delete [](unsigned char *)_items;
  _items = p;
  _capacity = newCapacity;
}
