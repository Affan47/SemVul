IsRunningInLANMode()
{
	if (thePrefs::FilterLanIPs() || !IsRunning()) {
		return false;
	}

	time_t now = time(NULL);
	if (m_lanModeCheck + 10 <= now) {
		m_lanModeCheck = now;
		uint32_t count = GetRoutingZone()->GetNumContacts();


		if (count == 0 || count > 256) {
			m_lanMode = false;
		} else {
			if (GetRoutingZone()->HasOnlyLANNodes()) {
				if (!m_lanMode) {
					m_lanMode = true;
					theApp->ShowConnectionState();
					AddDebugLogLineN(logKadMain, wxT("Activating LAN mode"));
				}
			} else {
				if (m_lanMode) {
					m_lanMode = false;
					theApp->ShowConnectionState();
					AddDebugLogLineN(logKadMain, wxT("Deactivating LAN mode"));
				}
			}
		}
	}
	return m_lanMode;
}
