headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return m_names[section];
    }
    else
    {
        return QVariant();
    }
}
