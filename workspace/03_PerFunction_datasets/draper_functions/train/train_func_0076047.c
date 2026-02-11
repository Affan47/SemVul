index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();


    Internal::AtcItem *parentItem = d->getItem(parent);
    Internal::AtcItem *childItem = 0;
    childItem = parentItem->child(row);

    if (childItem) {
        return createIndex(row, column, childItem);
    }
    return QModelIndex();
}
