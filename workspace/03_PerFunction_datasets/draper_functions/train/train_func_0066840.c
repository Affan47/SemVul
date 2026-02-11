SendNullPacket(uint8_t opcode, uint32_t ip, uint16_t port, const CKadUDPKey& targetKey, const CUInt128* cryptTargetID)
{
	CMemFile packetdata(0);
	SendPacket(packetdata, opcode, ip, port, targetKey, cryptTargetID);
}
