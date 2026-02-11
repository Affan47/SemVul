Unknown06()
{
	uint16_t expect = 0;

	Data command(-1, 8), response;
	JVMPacket packet(command, response);


	packet.Unknown06();
	m_socket->Packet(packet);
	expect = packet.Size();

	if (expect == 0)
		return;


	m_socket->Receive(response);

	size_t bytereceived = response.GetSize() - SB_JVMPACKET_HEADER_SIZE;


	if( expect != bytereceived ) {
		ThrowJVMError(string("JVMDebug::Unknown06(): ") + _("byte count mismatch"), expect);
	}
}
