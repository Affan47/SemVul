ProcessFirewalledRequest(const uint8_t *packetData, uint32_t lenPacket, uint32_t ip, uint16_t port, const CKadUDPKey& senderKey)
{

	CHECK_PACKET_EXACT_SIZE(2);

	CMemFile bio(packetData, lenPacket);
	uint16_t tcpport = bio.ReadUInt16();

	CUInt128 zero;
	CContact contact(zero, ip, port, tcpport, 0, 0, false, zero);
	if (!theApp->clientlist->RequestTCP(&contact, 0)) {
		return;
	}


	CMemFile packetdata(4);
	packetdata.WriteUInt32(ip);
	DebugSend(KadFirewalledRes, ip, port);
	SendPacket(packetdata, KADEMLIA_FIREWALLED_RES, ip, port, senderKey, NULL);
}
