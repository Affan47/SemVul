RemoveClients()
{
	bool res;

	m_Mutex.Lock();

	res = false;


	if ( m_pClientList != 0 )
	{
		CSearchClient * client = 0;


		while ( ( (client = m_pClientList->Next(client)) != NULL) )
		{
			if ( client->m_bSearchRemove )
			{
				if ( client->m_tSearchTimeout == 0 )
				{
					client->SetCallBackFunction(0);

					m_pClientList->Remove(client);
					delete client;

					client = 0;
				}

				else
				{
					if ( ((m_eClientMode == ecmACTIVE) &&
					      ((time(0) - client->m_tSearchTimeout) >= SEARCH_ACTIVE_CLIENT_REMOVE_TIMEOUT)) ||
					     ((m_eClientMode == ecmPASSIVE) &&
					      ((time(0) - client->m_tSearchTimeout) >= SEARCH_PASSIVE_CLIENT_REMOVE_TIMEOUT)) )
					{
						client->m_tSearchTimeout = 0;
						client->Disconnect(true);
					}
				}
			}
		}


		if ( m_pClientList->Count() == 0 )
		{
			res = true;
		}
	}
	else
	{
		res = true;
	}

	m_Mutex.UnLock();

	return res;
}
