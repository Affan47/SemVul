OpenTemp( CString & filename )
{
	bool ok = false;

	if ( (m_nFD != -1) || filename.IsEmpty() )
	{
		return ok;
	}

	m_nBufferPos = 0;
	m_nMode = IO_RAW | IO_WRITEONLY | IO_CREAT;

	CString tempname = filename;
	tempname += ".XXXXXX";

#ifdef WIN32
	char * res = _mktemp( tempname.Data() );

	if ( res )
	{
		ok = Open( tempname, m_nMode );
		if ( ok )
		{
			filename = tempname;
		}
	}
	else
	{
		ok = false;
	}
#else
	m_nFD = mkstemp( tempname.Data() );

	if ( m_nFD != -1 )
	{
		ok = true;
		m_pBuffer = new CByteArray(FILE_BUFFER_SIZE);
		filename = tempname;
	}
#endif
	return ok;
}
