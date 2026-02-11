RefreshSingleInstanceChecker()
{
#if defined(__WXMAC__) && defined(AMULE_DAEMON)

#else
	delete m_singleInstance;
	m_singleInstance = new wxSingleInstanceChecker(wxT("muleLock"), ConfigDir);
#endif
}
