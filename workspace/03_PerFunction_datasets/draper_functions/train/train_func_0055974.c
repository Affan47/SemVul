FindCase( const CString & string, long nStart ) const
{
	const char * sz = string.Data();
	const long len  = string.Length();

	if ( m_nStringLength == 0 )
	{
		if ( sz != 0 )
			return -1;
		else
			return 0;
	}

	if ( !sz )
		return -1;

	if ( (nStart+len) > m_nStringLength )
		return -1;
#ifdef HAVE_STRCASESTR

	const char * location = strcasestr( m_szBuffer + nStart, sz );

	if ( location == NULL )
	{
		return -1;
	}
	else
	{
		return location - m_szBuffer;
	}

#else

	for ( long i = nStart; i <= (m_nStringLength-len); ++i )
	{
#ifdef WIN32
		if ( _strnicmp(sz,m_szBuffer+i,len) == 0 )
#else
		if ( strncasecmp(sz,m_szBuffer+i,len) == 0 )
#endif
		{
			return i;
		}
	}

	return -1;

#endif
}
