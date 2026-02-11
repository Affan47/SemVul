setFileUtf8(const QString& s, bool utf8)
{
    if(DatabaseListEntry* e = FindEntry(s))
    {
        if(e->m_utf8 != utf8)
        {
            e->m_utf8 = utf8;
            QModelIndex m = createIndex(m_databases.indexOf(*e), DBLV_UTF8, (void*) 0);
            emit QAbstractItemModel::dataChanged(m, m);
        }
    }
}
