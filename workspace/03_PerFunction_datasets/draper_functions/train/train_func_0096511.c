Packet(Barry::JLPacket &packet, int timeout)
{
	if( packet.HasData() ) {
		SyncSend(packet.m_cmd);
		PacketData(packet.m_data, *packet.m_receive, false, timeout);
	}
	else {
		PacketData(packet.m_cmd, *packet.m_receive, false, timeout);
	}
}
