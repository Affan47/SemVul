rowCount(const QModelIndex &parent) const
{

    if (parent.isValid()) return 0;

    return d->m_SqlPatient->rowCount();
}
