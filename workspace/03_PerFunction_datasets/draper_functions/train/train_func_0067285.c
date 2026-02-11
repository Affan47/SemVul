OnSocketEvent(CSocketEvent &event)
{
	if (m_pProxyBackend)
	{
		switch (event.GetType())
		{
		case CSocketEvent::connection:
			{
				const int error = event.GetError();
				if (error)
				{
					m_pControlSocket->LogMessage(::Error, _("Proxy handshake failed: %s"), CSocket::GetErrorDescription(error).c_str());
					TransferEnd(failure);
				}
				else
				{
					delete m_pProxyBackend;
					m_pProxyBackend = 0;
					OnConnect();
				}
			}
			return;
		case CSocketEvent::close:
			{
				const int error = event.GetError();
				m_pControlSocket->LogMessage(::Error, _("Proxy handshake failed: %s"), CSocket::GetErrorDescription(error).c_str());
				TransferEnd(failure);
			}
			return;
		default:

			return;
		}
		return;
	}

	if (m_pSocketServer)
	{
		if (event.GetType() == CSocketEvent::connection)
			OnAccept(event.GetError());
		else
			m_pControlSocket->LogMessage(::Debug_Info, _T("Unhandled socket event %d from listening socket"), event.GetType());
		return;
	}

	switch (event.GetType())
	{
	case CSocketEvent::connection:
		if (event.GetError())
		{
			if (!m_transferEndReason)
			{
				m_pControlSocket->LogMessage(::Error, _("The data connection could not be established: %s"), CSocket::GetErrorDescription(event.GetError()).c_str());
				TransferEnd(transfer_failure);
			}
		}
		else
			OnConnect();
		break;
	case CSocketEvent::read:
		OnReceive();
		break;
	case CSocketEvent::write:
		OnSend();
		break;
	case CSocketEvent::close:
		OnClose(event.GetError());
		break;
	case CSocketEvent::hostaddress:

		break;
	default:
		m_pControlSocket->LogMessage(::Debug_Info, _T("Unhandled socket event %d"), event.GetType());
		break;
	}
}
