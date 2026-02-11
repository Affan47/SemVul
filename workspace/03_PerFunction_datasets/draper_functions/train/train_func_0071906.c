ConnectToServer(CServer* server, bool bNoCrypt)
{
	AddDebugLogLineN(logServer, wxT("Trying to connect"));

	if (cur_server){
		wxFAIL;
		delete cur_server;
		cur_server = NULL;
	}

	cur_server = new CServer(server);

	m_bNoCrypt = bNoCrypt;

	SetConnectionState(CS_CONNECTING);

	info = cur_server->GetListName();


	if (cur_server->HasDynIP() || !cur_server->GetIP()) {
		m_IsSolving = true;

		CAsyncDNS* dns = new CAsyncDNS(server->GetAddress(), DNS_SERVER_CONNECT, theApp, this);

		if ( dns->Create() == wxTHREAD_NO_ERROR ) {
			if ( dns->Run() != wxTHREAD_NO_ERROR ) {
				dns->Delete();
				AddLogLineN(CFormat( _("Cannot create DNS solving thread for connecting to %s") ) % cur_server->GetAddress());
			}
		} else {
			dns->Delete();
			AddLogLineN(CFormat( _("Cannot create DNS solving thread for connecting to %s") ) % cur_server->GetAddress());
		}
	} else {

		OnHostnameResolved(cur_server->GetIP());
	}

}
