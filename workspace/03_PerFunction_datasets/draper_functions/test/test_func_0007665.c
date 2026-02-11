TrustCurrentCert(bool trusted)
{
	if (m_tlsState != verifycert)
	{
		m_pOwner->LogMessage(Debug_Warning, _T("TrustCurrentCert called at wrong time."));
		return;
	}

	if (trusted)
	{
		m_tlsState = conn;

		if (m_lastWriteFailed)
			m_lastWriteFailed = false;
		CheckResumeFailedReadWrite();

		if (m_tlsState == conn)
		{
			CSocketEvent *evt = new CSocketEvent(m_pEvtHandler, this, CSocketEvent::connection);
			CSocketEventDispatcher::Get().SendEvent(evt);
		}

		TriggerEvents();

		return;
	}

	m_pOwner->LogMessage(::Error, _("Remote certificate not trusted."));
	Failure(0, ECONNABORTED);
}
