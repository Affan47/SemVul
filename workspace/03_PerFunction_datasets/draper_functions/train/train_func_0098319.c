init()
{
    MANGOS_ASSERT(!m_pTrans);
    m_pTrans = new SqlTransaction;
    return m_pTrans;
}
