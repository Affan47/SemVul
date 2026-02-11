HandleControlTransfer( const char * buffer, int len )
{
	CString s;
	int i,p = 0;


	for(i=0;i<len;i++)
	{
		if ( buffer[i] == '|' )
		{
			s = sBuffer;
			s += CString().Set(buffer,i+1);
			break;
		}
	}

	if ( i == len )
		i = -1;
	i++;

	if ( i > 0 )
	{
		p = HandleMessage( s.Data(), i );


		if ( (p < s.Length()) && (!m_bIdle) && (eMode == estTRANSFERDOWNLOAD) )
		{
			DPRINTF("WARNING: transfer->client send unwanted data ! [%d %d %d]\n",i,p,len);
		}
	}

	if ( (i == s.Length()) || ((!m_bIdle) && (eMode == estTRANSFERDOWNLOAD)) )
	{
		sBuffer.Empty();
	}
	else
	{
		sBuffer = s.Mid( i, s.Length()-i );
		p = len;
	}

	return p;
}
