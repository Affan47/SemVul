GetStmt( int nIndex )
{
    if(nIndex < 0)
        return NULL;


    if(m_holder.size() <= nIndex)
        m_holder.resize(nIndex + 1, NULL);

    SqlPreparedStatement * pStmt = NULL;


    if(m_holder[nIndex] == NULL)
    {

        std::string fmt = m_db.GetStmtString(nIndex);
        MANGOS_ASSERT(fmt.length());

        pStmt = CreateStatement(fmt);

        if(!pStmt->prepare())
        {
            MANGOS_ASSERT(false && "Unable to prepare SQL statement");
            return NULL;
        }


        m_holder[nIndex] = pStmt;
    }
    else
        pStmt = m_holder[nIndex];

    return pStmt;
}
