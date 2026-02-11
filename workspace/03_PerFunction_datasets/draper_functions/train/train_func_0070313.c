ServerSocketHandler(wxSocketEvent& event)
{
	CServerSocket *socket = dynamic_cast<CServerSocket *>(event.GetSocket());
	wxASSERT(socket);
	if (!socket) {
		return;
	}

	if (socket->OnDestroy()) {
		return;
	}

	switch(event.GetSocketEvent()) {
		case wxSOCKET_CONNECTION:
			socket->OnConnect(wxSOCKET_NOERROR);
			break;
		case wxSOCKET_LOST:
			socket->OnError(socket->LastError());
			break;
		case wxSOCKET_INPUT:
			socket->OnReceive(wxSOCKET_NOERROR);
			break;
		case wxSOCKET_OUTPUT:
			socket->OnSend(wxSOCKET_NOERROR);
			break;
		default:
			wxFAIL;
			break;
	}


}
