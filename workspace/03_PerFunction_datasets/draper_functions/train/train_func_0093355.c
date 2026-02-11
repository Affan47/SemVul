OnRun()
{
	if (!thePrefs::AcceptExternalConnections()) {

#if 0
		AddLogLineCS(_("ERROR: aMule daemon cannot be used when external connections are disabled. To enable External Connections, use either a normal aMule, start amuled with the option --ec-config or set the key \"AcceptExternalConnections\" to 1 in the file ~/.aMule/amule.conf"));
#else
		AddLogLineCS(_("ERROR: aMule AdunanzA daemon cannot be used when external connections are disabled. To enable External Connections, use either a normal aMule AdunanzA, start amuled AdunanzA with the option --ec-config or set the key \"AcceptExternalConnections\" to 1 in the file ~/.aMuleAdunanzA/amule.conf"));
#endif

		return 0;
	} else if (thePrefs::ECPassword().IsEmpty()) {

#if 0
		AddLogLineCS(_("ERROR: A valid password is required to use external connections, and aMule daemon cannot be used without external connections. To run aMule deamon, you must set the \"ECPassword\" field in the file ~/.aMule/amule.conf with an appropriate value. Execute amuled with the flag --ec-config to set the password. More information can be found at http://wiki.amule.org"));
#else
		AddLogLineCS(_("ERROR: A valid password is required to use external connections, and aMule AdunanzA daemon cannot be used without external connections. To run aMule AdunanzA deamon, you must set the \"ECPassword\" field in the file ~/.aMuleAdunanzA/amule.conf with an appropriate value. Execute amuled AdunanzA with the flag --ec-config to set the password."));
#endif

		return 0;
	}

#ifndef __WXMSW__


	int ret = 0;
	ret = sigaction(SIGCHLD, NULL, &m_oldSignalChildAction);
	m_newSignalChildAction = m_oldSignalChildAction;
	m_newSignalChildAction.sa_sigaction = OnSignalChildHandler;
	m_newSignalChildAction.sa_flags |=  SA_SIGINFO;
	m_newSignalChildAction.sa_flags &= ~SA_RESETHAND;
	ret = sigaction(SIGCHLD, &m_newSignalChildAction, NULL);
	if (ret == -1) {
		AddDebugLogLineC(logStandard, CFormat(wxT("CamuleDaemonApp::OnRun(): Installation of SIGCHLD callback with sigaction() failed: %m.")));
	} else {
		AddDebugLogLineN(logGeneral, wxT("CamuleDaemonApp::OnRun(): Installation of SIGCHLD callback with sigaction() succeeded."));
	}
#endif

#ifdef AMULED28

	while ( !m_Exit ) {
		m_table->RunSelect();
		ProcessPendingEvents();
		((CDaemonAppTraits *)GetTraits())->DeletePending();
	}


	ShutDown();

	return 0;

#else

#ifdef AMULED_DUMMY
	return 0;
#else
	return wxApp::OnRun();
#endif

#endif
}
