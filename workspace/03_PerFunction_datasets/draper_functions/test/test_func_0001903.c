AddContact(const uint8_t *data, uint32_t lenData, uint32_t ip, uint16_t port, uint16_t tport, const CKadUDPKey& udpKey, bool& ipVerified, bool update, CUInt128* outContactID)
{

#if 0

	if (!CAdunanzAUtilities::AduIsValidKaduAddress(ip) )
	{
		AddDebugLogLineM(false, logKadMain, CFormat(wxT("Skipping addContact non kADU %s")) % Uint32_16toStringIP_Port(wxUINT32_SWAP_ALWAYS(ip), port));
		return;
	}

#endif
	CMemFile bio(data, lenData);
	CUInt128 id = bio.ReadUInt128();
	if (outContactID != NULL) {
		*outContactID = id;
	}
	bio.ReadUInt32();
	bio.ReadUInt16();
	if (tport) {
		bio.ReadUInt16();
	} else {
		tport = bio.ReadUInt16();
	}
	bio.ReadUInt8();


	return CKademlia::GetRoutingZone()->Add(id, ip, port, tport, 0, udpKey, ipVerified, update, true);
}
