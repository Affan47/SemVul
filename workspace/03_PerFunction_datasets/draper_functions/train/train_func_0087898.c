flush( void)
{
	RCODE			rc = FERR_OK;

	flmAssert( m_bSetup);

	if( m_fnWrite && m_pThread)
	{
		if( *m_puiInOffset)
		{
			if( RC_BAD( rc = signalThread()))
			{
				goto Exit;
			}
		}


		if( RC_BAD( rc = f_semWait( m_hIdleSem, F_WAITFOREVER)))
		{
			goto Exit;
		}


		rc = m_rc;


		f_semSignal( m_hIdleSem);


		if( RC_BAD( rc))
		{
			goto Exit;
		}
	}

Exit:

	return( rc);
}
