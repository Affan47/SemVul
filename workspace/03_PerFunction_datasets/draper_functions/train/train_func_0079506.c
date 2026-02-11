GetBIStream(
	FCS_BIOS **	 ppBIStream)
{
	RCODE rc = FERR_OK;

	*ppBIStream = NULL;

	if (!m_pBIStream)
	{
		m_pBIStream = f_new FCS_BIOS;
		if (!m_pBIStream)
		{
			rc = RC_SET( FERR_MEM);
			goto Exit;
		}
	}

	*ppBIStream = m_pBIStream;

Exit:

	return (rc);
}
