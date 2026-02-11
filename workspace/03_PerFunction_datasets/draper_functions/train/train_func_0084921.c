OnHostnameResolved(uint32 ip) {

	m_IsSolving = false;
	if (ip) {
		if (theApp->ipfilter->IsFiltered(ip, true)) {
			AddLogLineC(CFormat( _("Server IP %s (%s) is filtered.  Not connecting.") )
				% Uint32toStringIP(ip) % cur_server->GetAddress() );
			OnConnect(wxSOCKET_INVADDR);
		} else {
			amuleIPV4Address addr;
			addr.Hostname(ip);
			uint16 nPort = 0;
			wxString useObfuscation;
			if ( !m_bNoCrypt && thePrefs::IsServerCryptLayerTCPRequested() && cur_server->GetObfuscationPortTCP() != 0 && cur_server->SupportsObfuscationTCP()){
				nPort = cur_server->GetObfuscationPortTCP();
				useObfuscation = _("using protocol obfuscation.");
				SetConnectionEncryption(true, NULL, true);
			} else {
				nPort = cur_server->GetConnPort();
				SetConnectionEncryption(false, NULL, true);
			}

			addr.Service(nPort);

			AddLogLineN(CFormat( _("Connecting to %s (%s - %s:%i) %s") )
				% cur_server->GetListName()
				% cur_server->GetAddress()
				% cur_server->GetFullIP()
				% nPort
				% useObfuscation
			);

			AddDebugLogLineN(logServer, CFormat(wxT("Server %s(%s) Port %i"))
				% cur_server->GetAddress() % Uint32toStringIP(ip) % cur_server->GetConnPort());
			Connect(addr, false);
		}
	} else {
		AddLogLineC(CFormat( _("Could not solve dns for server %s: Unable to connect!") )
			% cur_server->GetAddress() );
		OnConnect(wxSOCKET_NOHOST);
	}

}
