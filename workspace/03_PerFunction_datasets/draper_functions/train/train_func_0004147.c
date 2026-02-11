Read( char * buf, long count )
{
	long i = -1;

	if ( (m_nFD == -1) || (count <= 0) || (!buf))
	{
		return i;
	}

#ifdef WIN32
	i = _read( m_nFD, buf, count );
#else
	i = read( m_nFD, buf, count );
#endif

	return i;
}
