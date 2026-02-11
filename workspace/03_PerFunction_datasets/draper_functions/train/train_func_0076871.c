Get_EC_Response_Search_Results_Download(const CECPacket *request)
{
	CECPacket *response = new CECPacket(EC_OP_STRINGS);
	for (CECPacket::const_iterator it = request->begin(); it != request->end(); it++) {
		const CECTag &tag = *it;
		CMD4Hash hash = tag.GetMD4Data();
		uint8 category = tag.GetFirstTagSafe()->GetInt();
		theApp->searchlist->AddFileToDownloadByHash(hash, category);
	}
	return response;
}
