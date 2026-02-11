expand()
{
    if (!m_usingTable)
        createTable();
    else
        rehash(m_u.table->size * 2);
}
