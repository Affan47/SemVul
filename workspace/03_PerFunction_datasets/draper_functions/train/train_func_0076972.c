operator=(const SqlStatement& index)
{
    if (this != &index)
    {
        m_index = index.m_index;
        m_pDB = index.m_pDB;

        delete m_pParams;
        m_pParams = NULL;

        if (index.m_pParams)
            { m_pParams = new SqlStmtParameters(*(index.m_pParams)); }
    }

    return *this;
}
