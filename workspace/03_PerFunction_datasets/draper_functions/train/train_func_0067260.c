contacts(const QList<QContactSortOrder>& sortOrders, const QContactFetchHint& fetchHint) const
{
    d->m_error = QContactManager::NoError;
    d->m_errorMap.clear();
    return d->m_engine->contacts(QContactFilter(), sortOrders, fetchHint, &d->m_error);
}
