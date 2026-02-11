insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count);
    for(int i = 0; i < count; ++i) {
        Calendar::People p;
        m_People.insert(row+i, p);
    }
    endInsertRows();
    return true;
}
