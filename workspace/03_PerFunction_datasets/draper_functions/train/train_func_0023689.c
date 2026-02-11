setupSession(
	F_SessionMgr *			pSessionMgr)
{
	RCODE		rc = FERR_OK;

	flmAssert( m_hMutex == F_MUTEX_NULL);
	flmAssert( pSessionMgr);

	if( RC_BAD( rc = f_mutexCreate( &m_hMutex)))
	{
		goto Exit;
	}

	if( (m_pDbTable = f_new F_HashTable) == NULL)
	{
		rc = RC_SET( FERR_MEM);
		goto Exit;
	}

	if( RC_BAD( rc = m_pDbTable->setupHashTable( FALSE, 16, 0)))
	{
		goto Exit;
	}

	m_pSessionMgr = pSessionMgr;

Exit:

	return( rc);
}
