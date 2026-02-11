ProcessRequestPartsPacketv2(const CMemFile& data) {

	CMD4Hash reqfilehash = data.ReadHash();

	uint8 numblocks = data.ReadUInt8();

	for (int i = 0; i < numblocks; i++) {
		Requested_Block_Struct* reqblock = new Requested_Block_Struct;
		try {
			reqblock->StartOffset = data.GetIntTagValue();

			reqblock->EndOffset = data.GetIntTagValue() + 1;
			if ((reqblock->StartOffset || reqblock->EndOffset) && (reqblock->StartOffset > reqblock->EndOffset)) {
				AddDebugLogLineN(logClient, CFormat(wxT("Client %s request is invalid! %d / %d"))
					% GetFullIP() % reqblock->StartOffset % reqblock->EndOffset);
				throw wxString(wxT("Client request is invalid!"));
			}

			AddDebugLogLineN(logClient,
				CFormat(wxT("Client %s requests %d File block %d-%d (%d bytes):"))
					% GetFullIP() % i % reqblock->StartOffset % reqblock->EndOffset
					% (reqblock->EndOffset - reqblock->StartOffset));

			md4cpy(reqblock->FileID, reqfilehash.GetHash());
			reqblock->transferred = 0;
			AddReqBlock(reqblock);
		} catch (...) {
			delete reqblock;
			throw;
		}
	}
}
