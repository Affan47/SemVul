isOpen( void)
{


	flmAssert( m_bSetupCalled == TRUE);

	if( m_pIStream && m_pIStream->isOpen())
	{
		return( TRUE);
	}

	return( FALSE);
}
