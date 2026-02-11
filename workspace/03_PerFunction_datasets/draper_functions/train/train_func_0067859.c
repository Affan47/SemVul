selectedIndex() const
{

    uint o = 0;
    const QVector<HTMLGenericFormElementImpl*> items = listItems();
    const unsigned int itemsSize = items.size();
    for (unsigned int i = 0; i < itemsSize; ++i) {
        if (items[i]->id() == ID_OPTION) {
            if (static_cast<HTMLOptionElementImpl*>(items[i])->selectedBit())
                return o;
            o++;
        }
    }

    return -1;
}
