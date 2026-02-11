InflateZBlock( const char * in, int * inlen, char * out, int * outlen )
{
	int res = -1;

	int i;

	if ( m_bInit == false )
	{
		m_bInit = true;

		m_pZStream->next_in   = 0;
		m_pZStream->avail_in  = 0;
		m_pZStream->opaque    = Z_NULL;
		m_pZStream->zalloc    = Z_NULL;
		m_pZStream->zfree     = Z_NULL;
		m_pZStream->total_out = 0;

		inflateInit(m_pZStream);
	}


	if ( (in != 0) && (*inlen != 0) )
	{
		m_pZStream->next_in   = (Bytef*)in;
		m_pZStream->avail_in  = *inlen;
	}

	if ( (out != 0) && (*outlen != 0) )
	{
		m_pZStream->next_out  = (Bytef*)out;
		m_pZStream->avail_out = *outlen;
	}

	i = inflate(m_pZStream,Z_SYNC_FLUSH);


	if  ( (i == Z_OK) || (i == Z_STREAM_END) || (i == Z_BUF_ERROR) )
	{
		*outlen = *outlen - m_pZStream->avail_out;
		*inlen  = *inlen - m_pZStream->avail_in;

		res = 1;

		if ( i == Z_STREAM_END )
		{
			inflateEnd(m_pZStream);
			m_bInit = false;
			res = 0;
		}
	}
	else
	{
		inflateEnd(m_pZStream);
		m_bInit = false;
		*outlen = 0;
		res = -1;
	}


	return res;
}
