lockSession(
	FLMBOOL			bWait)
{
	RCODE		rc = FERR_OK;

	flmAssert( getRefCount());
	f_mutexLock( m_hMutex);

	if( m_uiThreadId && m_uiThreadId != f_threadId())
	{
		if( !bWait)
		{
			rc = RC_SET( FERR_TIMEOUT);
			goto Exit;
		}

		if( RC_BAD( rc = f_notifyWait( m_hMutex, F_SEM_NULL, NULL,
			&m_pNotifyList)))
		{
			goto Exit;
		}
	}

	m_uiThreadId = f_threadId();
	m_uiThreadLockCount++;

Exit:

	f_mutexUnlock( m_hMutex);
	return( rc);
}
