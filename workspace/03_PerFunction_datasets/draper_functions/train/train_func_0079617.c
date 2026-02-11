RollbackTransaction()
{
    if (!m_pAsyncConn)
        { return false; }

    if (!m_TransStorage->get())
        { return false; }


    m_TransStorage->reset();

    return true;
}
