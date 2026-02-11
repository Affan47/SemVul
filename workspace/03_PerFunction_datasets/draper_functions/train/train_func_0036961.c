SendUDPPacket(CPacket* packet, CServer* host, bool delpacket, bool rawpacket, uint16 port_offset)
{
	if (connected) {
		serverudpsocket->SendPacket(packet, host, delpacket, rawpacket, port_offset);
	} else if (delpacket) {
		delete packet;
	}

	return true;
}
