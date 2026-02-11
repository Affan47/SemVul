InitLogFile() const
{
	if (m_logfile_initialized)
		return;

	m_logfile_initialized = true;

	m_file = m_pEngine->GetOptions()->GetOption(OPTION_LOGGING_FILE);
	if (m_file == _T(""))
		return;

#ifdef __WXMSW__
	m_log_fd = CreateFile(m_file, FILE_APPEND_DATA, FILE_SHARE_DELETE | FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (m_log_fd == INVALID_HANDLE_VALUE)
#else
	m_log_fd = open(m_file.fn_str(), O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (m_log_fd == -1)
#endif
	{
		LogMessage(Error, _("Could not open log file: %s"), wxSysErrorMsg());
		return;
	}

	m_prefixes[Status] = _("Status:");
	m_prefixes[Error] = _("Error:");
	m_prefixes[Command] = _("Command:");
	m_prefixes[Response] = _("Response:");
	m_prefixes[Debug_Warning] = _("Trace:");
	m_prefixes[Debug_Info] = m_prefixes[Debug_Warning];
	m_prefixes[Debug_Verbose] = m_prefixes[Debug_Warning];
	m_prefixes[Debug_Debug] = m_prefixes[Debug_Warning];
	m_prefixes[RawList] = _("Listing:");

	m_pid = wxGetProcessId();

	m_max_size = m_pEngine->GetOptions()->GetOptionVal(OPTION_LOGGING_FILE_SIZELIMIT);
	if (m_max_size < 0)
		m_max_size = 0;
	else if (m_max_size > 2000)
		m_max_size = 2000;
	m_max_size *= 1024 * 1024;
}
