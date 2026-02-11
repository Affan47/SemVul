RollbackTransaction()

{
#if (ODBCVER >= 0x0300)

    if (m_bInTransaction)
    {
        m_bInTransaction = FALSE;

        int nRetCode = SQLEndTran( SQL_HANDLE_DBC, m_hDBC, SQL_ROLLBACK );

        if( nRetCode != SQL_SUCCESS && nRetCode != SQL_SUCCESS_WITH_INFO )
            return FALSE;
    }

#endif
    return TRUE;
}
