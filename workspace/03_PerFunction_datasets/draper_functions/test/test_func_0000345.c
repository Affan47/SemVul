IsUserOnline( CString & nick )
{
	bool res = false;

	if ( nick.IsEmpty() )
	{
		return res;
	}

	m_Mutex.Lock();

	res = ( m_MyInfoMap.find(nick) != m_MyInfoMap.end() );

	m_Mutex.UnLock();

	return res;
}
