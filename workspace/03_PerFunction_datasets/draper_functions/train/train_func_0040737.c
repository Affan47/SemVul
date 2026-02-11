RemoveUser( CString & nick )
{
	if ( nick.IsEmpty() )
	{
		return;
	}

	CMessageMyInfo *myinfo=0;

	m_Mutex.Lock();

	MyInfoMap::iterator it = m_MyInfoMap.find(nick);
	if ( it != m_MyInfoMap.end() )
	{
		myinfo = it->second;

		if ( myinfo->m_nShared > m_nShareSize )
			m_nShareSize = 0;
		else
			m_nShareSize -= myinfo->m_nShared;

		m_MyInfoMap.erase( it );
		delete myinfo;
	}

	m_Mutex.UnLock();
}
