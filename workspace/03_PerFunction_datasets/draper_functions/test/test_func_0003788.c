flags(const QModelIndex &index) const
{
    if (index.isValid() && index == mEditIndex)
    {
        return Qt::ItemIsEnabled|Qt::ItemIsEditable;
    }

    return Qt::ItemIsEnabled;
}
