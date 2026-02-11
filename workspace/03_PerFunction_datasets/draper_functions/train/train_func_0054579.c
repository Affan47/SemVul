TransferEnd(enum TransferEndReason reason)
{
	m_pControlSocket->LogMessage(::Debug_Verbose, _T("CTransferSocket::TransferEnd(%d)"), reason);

	if (m_transferEndReason != none)
		return;
	m_transferEndReason = reason;

	delete m_pSocketServer;
	m_pSocketServer = 0;

	delete m_pProxyBackend;
	m_pProxyBackend = 0;

	if (m_pTlsSocket)
	{
		if (m_pBackend == m_pTlsSocket)
			m_pBackend = 0;
		delete m_pTlsSocket;
		m_pTlsSocket = 0;
	}

	delete m_pBackend;
	m_pBackend = 0;

	delete m_pSocket;
	m_pSocket = 0;

	m_pEngine->SendEvent(engineTransferEnd);
}
