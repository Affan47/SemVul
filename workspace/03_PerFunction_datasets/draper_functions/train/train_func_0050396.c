removeRows(int row, int count, const QModelIndex &parent)
{
    int max = row+count;
    beginRemoveRows(parent, row, max-1);
    for(int i=0; i < count; ++i) {
        d->m_Labels.removeAt(row);
    }
    endRemoveRows();
    return true;
}
