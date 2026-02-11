fetchMore(const QModelIndex &parent)
{
    if (d->m_SqlPatient)
        d->m_SqlPatient->fetchMore(parent);
}
