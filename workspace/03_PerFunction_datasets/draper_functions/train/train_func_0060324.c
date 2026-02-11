removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent,row,row+count);
    int i;
    for(i=0; i<count;++i) {
        if ((i+row) < d->m_StringList.count())
            d->m_StringList.removeAt(i+row);
    }
    endRemoveRows();
    return true;
}
