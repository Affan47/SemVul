Process2SearchNotesRequest(const uint8_t *packetData, uint32_t lenPacket, uint32_t ip, uint16_t port, const CKadUDPKey& senderKey)
{
	CMemFile bio(packetData, lenPacket);
	CUInt128 target = bio.ReadUInt128();
	uint64_t fileSize = bio.ReadUInt64();
	CKademlia::GetIndexed()->SendValidNoteResult(target, ip, port, fileSize, senderKey);
}
