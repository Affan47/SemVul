SubStart( unsigned int i ) const
{
	ClearErrorString();
	int ret = -1;
	if ( rc )
		ret = rc->startp[safeIndex(i)] - str;
	else
		m_szError = CRegErrorHandler::FindErr( REGERR_NO_REGEXP );
	return ret;
}
