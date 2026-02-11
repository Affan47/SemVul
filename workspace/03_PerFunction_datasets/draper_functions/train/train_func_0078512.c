OnConnect()
{
	m_pControlSocket->SetAlive();
	m_pControlSocket->LogMessage(::Debug_Verbose, _T("CTransferSocket::OnConnect"));

	if (!m_pSocket)
	{
		m_pControlSocket->LogMessage(::Debug_Verbose, _T("CTransferSocket::OnConnect called without socket"));
		return;
	}

	if (!m_pBackend)
	{
		if (!InitBackend())
		{
			TransferEnd(transfer_failure);
			return;
		}
	}
	else if (m_pTlsSocket)
	{
		if (CServerCapabilities::GetCapability(*m_pControlSocket->m_pCurrentServer, tls_resume) == unknown)
		{
			CServerCapabilities::SetCapability(*m_pControlSocket->m_pCurrentServer, tls_resume, m_pTlsSocket->ResumedSession() ? yes : no);
		}
	}

	if (m_bActive)
		TriggerPostponedEvents();
}
