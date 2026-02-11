UpdateStats()
{
	if (m_lastClientSoft != m_clientSoft || m_lastClientVersion != m_nClientVersion || m_lastOSInfo != m_sClientOSInfo) {
		if (m_lastClientSoft == SO_UNKNOWN) {
			theStats::RemoveUnknownClient();
		} else if (m_lastClientSoft != (uint32)(-1)) {
			theStats::RemoveKnownClient(m_lastClientSoft, m_lastClientVersion, m_lastOSInfo);
		}

		m_lastClientSoft = m_clientSoft;
		m_lastClientVersion = m_nClientVersion;
		m_lastOSInfo = m_sClientOSInfo;

		if (m_clientSoft == SO_UNKNOWN) {
			theStats::AddUnknownClient();
		} else {
			theStats::AddKnownClient(this);
		}
	}
}
