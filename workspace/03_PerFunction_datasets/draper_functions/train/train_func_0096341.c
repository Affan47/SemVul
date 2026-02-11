OnPacketReceived(const CECPacket *packet, uint32 trueSize)
{
	packet->DebugPrint(true, trueSize);

	const CECPacket *reply = NULL;

	if (m_conn_state == CONN_FAILED) {

		AddLogLineN(_("Client sent packet after authentication failed."));
		CloseSocket();
	}

	if (m_conn_state != CONN_ESTABLISHED) {


		reply = Authenticate(packet);
	} else {
		reply = ProcessRequest2(packet);
	}
	return reply;
}
