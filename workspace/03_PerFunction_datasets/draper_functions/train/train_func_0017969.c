Append( const unsigned char * pchSrc, unsigned long nSize )
{
	unsigned char *p;
	unsigned char * temp;


	if ( (nSize == 0) || (pchSrc == NULL) )
	{
		return;
	}


	if ( (pchSrc >= m_pchBuffer) && (pchSrc <= m_pchBuffer+m_nBufferSize) )
	{
		temp = (unsigned char*) malloc( nSize );
		if ( temp == NULL )
		{
			perror("CByteArray::Append malloc");
			return;
		}
		memcpy(temp,pchSrc,nSize);

	}
	else
	{
		temp = (unsigned char*) pchSrc;
	}

	if ( (m_nSize+nSize) > m_nBufferSize )
	{

		m_nBufferSize += nSize + 10000;
		p = (unsigned char*) realloc(m_pchBuffer,m_nBufferSize);

		if ( p == NULL )
		{
			m_nBufferSize -= (nSize + 10000);
			perror("CByteArray::Append realloc");

			if ( temp != pchSrc )
			{
				free(temp);
			}

			return;
		}

		m_pchBuffer = p;
	}


	memcpy( m_pchBuffer+m_nSize, temp, nSize );

	m_nSize += nSize;

	if ( temp != pchSrc )
	{
		free(temp);
	}
}
