CommitTransactionDirect()
{
    if (!m_pAsyncConn)
        return false;


    if(!m_TransStorage->get())
        return false;


    SqlTransaction * pTrans = m_TransStorage->detach();
    pTrans->Execute(m_pAsyncConn);
    delete pTrans;

    return true;
}
