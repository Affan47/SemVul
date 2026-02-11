GetNick( CString hubname, CString hubhost )
{
	CString res;
	CClient* client;

	if ( !m_pClientList )
	{
		return res;
	}

	m_pClientListMutex->Lock();

	if ( (client = GetHubObject( hubname, hubhost )) != 0 )
	{
		res = client->GetNick();
	}

	m_pClientListMutex->UnLock();

	return res;
}
