ProcessItemUpdate(CEC_Friend_Tag * tag, CFriend * Friend)
{
	if (!tag->HasChildTags()) {
		return;
	}
	tag->Name(Friend->m_strName);
	tag->UserHash(Friend->m_UserHash);
	tag->IP(Friend->m_dwLastUsedIP);
	tag->Port(Friend->m_nLastUsedPort);
	uint32 clientID;
	bool notified = false;
	if (tag->Client(clientID)) {
		if (clientID) {
			CClientRef * client = theApp->clientlist->GetByID(clientID);
			if (client) {
				Friend->LinkClient(*client);
				notified = true;
			}
		} else {

			Friend->UnLinkClient(false);
		}
	}
	if (!notified) {
		Notify_ChatUpdateFriend(Friend);
	}
}
