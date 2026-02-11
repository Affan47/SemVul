GetTCPHostString( bool addport, bool crypto )
{
	CString s;
	unsigned int n = 0;


	if ( crypto )
	{
		if ( CCryptoListenManager::Instance() )
		{
			n = CCryptoListenManager::Instance()->GetListenPort();
		}
	}
	else
	{
		if ( CListenManager::Instance() )
		{
			n = CListenManager::Instance()->GetListenPort();
		}
	}

	m_Mutex.Lock();

	if ( m_sHost.NotEmpty() )
	{
		if ( m_bExternalIP )
		{

			if ( (m_sHostCache.IsEmpty()) ||
		     	     ((time(0)-m_tHostTimeout) > 60) )
			{
				m_sHostCache   = CNetAddr::GetHostI4(m_sHost.Replace(' ',""));
				m_tHostTimeout = time(0);
			}

			s = m_sHostCache;
		}
		else
		{
			s = CNetAddr::GetInterfaceI4( m_sHost );
		}
	}

	if ( s.NotEmpty() && addport )
	{
		if ( n != 0 )
		{
			s += ':';
			s += CString::number(n);
		}
		else
		{
			s.Empty();
		}
	}

	m_Mutex.UnLock();

	return s;
}
