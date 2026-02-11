setCurrentItem( const QString& item, bool insert, int index )
{
    int sel = -1;

    const int itemCount = count();
    for (int i = 0; i < itemCount; ++i)
    {
        if (itemText(i) == item)
        {
            sel = i;
            break;
        }
    }

    if (sel == -1 && insert)
    {
        if (index >= 0) {
            insertItem(index, item);
            sel = index;
        } else {
            addItem(item);
            sel = count() - 1;
        }
    }
    setCurrentIndex(sel);
}
