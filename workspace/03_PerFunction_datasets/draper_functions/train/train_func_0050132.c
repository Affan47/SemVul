set_item(int i, Type1Item *it)
{
    delete _items[i];
    _items[i] = it;
}
