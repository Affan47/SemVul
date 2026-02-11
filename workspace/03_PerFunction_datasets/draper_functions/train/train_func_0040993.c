GetUserMyInfo( CString nick, CMessageMyInfo * p )
{
	bool res = false;

	if ( nick.IsEmpty() )
	{
		return res;
	}

	m_Mutex.Lock();

	MyInfoMap::const_iterator it = m_MyInfoMap.find(nick);
	if ( it != m_MyInfoMap.end() )
	{
		*p = *(it->second);
		res = true;
	}

	m_Mutex.UnLock();

	return res;
}
