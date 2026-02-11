DoReceive()
{
	do
	{
		const enum CSocket::SocketState state = m_pSocket->GetState();
		if (state != CSocket::connected && state != CSocket::closing)
			return 0;

		if (!m_pRecvBuffer)
		{
			m_pRecvBuffer = new char[m_recvBufferLen];
			m_recvBufferPos = 0;
		}

		unsigned int len = m_recvBufferLen - m_recvBufferPos;
		int error;
		int read = m_pBackend->Read(m_pRecvBuffer + m_recvBufferPos, len, error);
		if (read == -1)
		{
			if (error != EAGAIN)
			{
				ResetOperation(FZ_REPLY_ERROR | FZ_REPLY_DISCONNECTED);
			}
			return 0;
		}

		m_pEngine->SetActive(CFileZillaEngine::recv);

		if (!m_pCurOpData || m_pCurOpData->opId == cmd_connect)
		{

			m_recvBufferPos = 0;
			return 0;
		}

		m_recvBufferPos += read;

		if (!m_pHttpOpData->m_gotHeader)
		{
			if (!read)
			{
				ResetOperation(FZ_REPLY_ERROR | FZ_REPLY_DISCONNECTED);
				return 0;
			}

			int res = ParseHeader(m_pHttpOpData);
			if ((res & FZ_REPLY_REDIRECTED) == FZ_REPLY_REDIRECTED)
				return FZ_REPLY_REDIRECTED;
			if (res != FZ_REPLY_WOULDBLOCK)
				return 0;
		}
		else if (m_pHttpOpData->m_transferEncoding == CHttpOpData::chunked)
		{
			if (!read)
			{
				ResetOperation(FZ_REPLY_ERROR | FZ_REPLY_DISCONNECTED);
				return 0;
			}
			OnChunkedData(m_pHttpOpData);
		}
		else
		{
			if (!read)
			{
				wxASSERT(!m_recvBufferPos);
				ProcessData(0, 0);
				return 0;
			}
			else
			{
				m_pHttpOpData->m_receivedData += m_recvBufferPos;
				ProcessData(m_pRecvBuffer, m_recvBufferPos);
				m_recvBufferPos = 0;
			}
		}
	}
	while (m_pSocket);

	return 0;
}
