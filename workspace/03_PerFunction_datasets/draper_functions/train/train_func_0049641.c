write(
	FLMBYTE *		pucData,
	FLMUINT			uiLength)
{
	RCODE		rc = FERR_OK;


	flmAssert( m_bSetupCalled == TRUE);


Retry_Write:

	if( FCS_DOS_BUFFER_SIZE - m_uiBOffset >= uiLength)
	{
		f_memcpy( &(m_pucBuffer[ m_uiBOffset]), pucData, uiLength);
		m_uiBOffset += uiLength;
	}
	else
	{
		if( m_uiBOffset > 0)
		{
			if( RC_BAD( rc = flush()))
			{
				goto Exit;
			}
		}

		if( uiLength <= FCS_DOS_BUFFER_SIZE)
		{
			goto Retry_Write;
		}

		if( RC_BAD( rc = m_pOStream->write( pucData, uiLength)))
		{
			goto Exit;
		}
	}

Exit:

	return( rc);
}
