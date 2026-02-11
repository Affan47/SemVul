setEquivalentUuid(const QStringList &list)
{
    d->m_EquivalentUuid = list;
    d->m_EquivalentUuid.removeDuplicates();
    d->m_EquivalentUuid.removeAll("");
}
