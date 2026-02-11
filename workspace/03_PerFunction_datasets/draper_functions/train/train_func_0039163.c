IsAdmin( CString hubname, CString hubhost, CString nick )
{
	bool res;
	CClient* client;

	if ( !m_pClientList )
	{
		return false;
	}

	m_pClientListMutex->Lock();

	res = false;

	if ( (client = GetHubObject(hubname,hubhost)) != 0 )
	{
		if ( client->IsHandshake() == false )
		{
			if ( nick.IsEmpty() )
				res = client->UserList()->IsAdmin( client->GetNick() );
			else
				res = client->UserList()->IsAdmin(nick);
		}
	}

	m_pClientListMutex->UnLock();

	return res;
}
