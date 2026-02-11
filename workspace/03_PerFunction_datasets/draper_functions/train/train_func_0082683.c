OnExit()
{
	if (m_app_state!=APP_STATE_STARTING) {
		AddLogLineNS(_("Now, exiting main app..."));
	}


#if !defined(CLIENT_GUI)
	if (rm) {
		std::cout << "AdunanzA says: delete remote settings..." << std::endl;
		m_bValidRemoteSettings = false;
		delete rm;
		rm = NULL;
		std::cout << "AdunanzA says: delete remote settings... Done!" << std::endl;
	}
	if (pUploadSlotsMng) {
		std::cout << "AdunanzA says: delete upload Slots Manager..." << std::endl;
		delete pUploadSlotsMng;
		pUploadSlotsMng = NULL;
		std::cout << "AdunanzA says: delete upload Slots Manager... Done!" << std::endl;
	}
#endif


	delete wxConfigBase::Set((wxConfigBase *)NULL);


	clientcredits->SaveList();


	if (webserver_pid) {
		AddLogLineNS(CFormat(_("Terminating amuleweb instance with pid '%ld' ... ")) % webserver_pid);
		wxKillError rc;
		if (wxKill(webserver_pid, wxSIGTERM, &rc) == -1) {
			AddLogLineNS(CFormat(_("Killing amuleweb instance with pid '%ld' ... ")) % webserver_pid);
			if (wxKill(webserver_pid, wxSIGKILL, &rc) == -1) {
				AddLogLineNS(_("Failed"));
			}
		}
	}

	if (m_app_state!=APP_STATE_STARTING) {
		AddLogLineNS(_("aMule OnExit: Terminating core."));
	}

	delete serverlist;
	serverlist = NULL;

	delete searchlist;
	searchlist = NULL;

	delete clientcredits;
	clientcredits = NULL;

	delete friendlist;
	friendlist = NULL;


	delete sharedfiles;
	sharedfiles = NULL;

	delete serverconnect;
	serverconnect = NULL;

	delete listensocket;
	listensocket = NULL;

	delete clientudp;
	clientudp = NULL;

	delete knownfiles;
	knownfiles = NULL;

	delete canceledfiles;
	canceledfiles = NULL;

	delete clientlist;
	clientlist = NULL;

	delete uploadqueue;
	uploadqueue = NULL;

	delete downloadqueue;
	downloadqueue = NULL;

	delete ipfilter;
	ipfilter = NULL;

#ifdef ENABLE_UPNP
	delete m_upnp;
	m_upnp = NULL;
#endif

	delete ECServerHandler;
	ECServerHandler = NULL;

	delete m_statistics;
	m_statistics = NULL;

	delete glob_prefs;
	glob_prefs = NULL;
	CPreferences::EraseItemList();

	delete uploadBandwidthThrottler;
	uploadBandwidthThrottler = NULL;

	if (m_app_state!=APP_STATE_STARTING) {
		AddLogLineNS(_("aMule shutdown completed."));
	}

#if wxUSE_MEMORY_TRACING
	AddLogLineNS(_("Memory debug results for aMule exit:"));

	wxLog* oldLog = wxLog::SetActiveTarget(new wxLogStderr);


	AddLogLineNS(wxT("***************Stats**************"));
	wxDebugContext::PrintStatistics(true);


	delete wxLog::SetActiveTarget(oldLog);
#endif

	StopTickTimer();


	return AMULE_APP_BASE::OnExit();
}
