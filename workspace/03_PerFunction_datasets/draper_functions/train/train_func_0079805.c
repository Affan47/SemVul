Write( const char * buf, long count )
{
	long i = 0;

	if ( (m_nFD == -1) || (count <= 0) || (!buf) )
	{
		return -1;
	}

	if ( (m_nMode & IO_WRITEONLY) != 0 )
	{
		if ( count >= FILE_BUFFER_SIZE )
		{
			i = Flush();
		}
		else if ( (count+m_nBufferPos) > FILE_BUFFER_SIZE )
		{
			i = Flush();

			if ( i != -1 )
			{
				m_nBufferPos = count;
				memcpy(m_pBuffer->Data(),buf,count);

				i = count;
			}
		}
		else
		{
			memcpy(m_pBuffer->Data()+m_nBufferPos,buf,count);
			m_nBufferPos += count;

			i = count;
		}
	}


	if ( i != -1 )
	{
		if ( m_nBufferPos == 0 )
		{
#ifdef WIN32
			i = _write( m_nFD, buf, count );
#else
			i = write( m_nFD, buf, count );
#endif
		}
	}

	return i;
}
