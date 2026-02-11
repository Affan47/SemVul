SendValidNoteResult(const CUInt128& keyID, uint32_t ip, uint16_t port, uint64_t fileSize, const CKadUDPKey& senderKey)
{
	SrcHash* currNoteHash = NULL;
	SrcHashMap::iterator itNote = m_Notes_map.find(keyID);
	if (itNote != m_Notes_map.end()) {
		currNoteHash = itNote->second;
		CMemFile packetdata(1024*50);
		packetdata.WriteUInt128(Kademlia::CKademlia::GetPrefs()->GetKadID());
		packetdata.WriteUInt128(keyID);
		packetdata.WriteUInt16(50);
		uint16_t maxResults = 150;
		uint16_t count = 0;

		for (CKadSourcePtrList::iterator itSource = currNoteHash->m_Source_map.begin(); itSource != currNoteHash->m_Source_map.end(); ++itSource ) {
			Source* currNote = *itSource;
			if (currNote->entryList.size()) {
				Kademlia::CEntry* currName = currNote->entryList.front();
				if (count < maxResults) {
					if (!fileSize || !currName->m_uSize || fileSize == currName->m_uSize) {
						packetdata.WriteUInt128(currName->m_uSourceID);
						currName->WriteTagList(&packetdata);
						count++;
						if (count % 50 == 0) {
							DebugSend(Kad2SearchRes, ip, port);
							CKademlia::GetUDPListener()->SendPacket(packetdata, KADEMLIA2_SEARCH_RES, ip, port, senderKey, NULL);

							packetdata.SetLength(16 + 16 + 2);
						}
					}
				} else {
					break;
				}
			}
		}

		uint16_t countLeft = count % 50;
		if (countLeft) {
			packetdata.Seek(16 + 16);
			packetdata.WriteUInt16(countLeft);
			DebugSend(Kad2SearchRes, ip, port);
			CKademlia::GetUDPListener()->SendPacket(packetdata, KADEMLIA2_SEARCH_RES, ip, port, senderKey, NULL);
		}
	}
}
