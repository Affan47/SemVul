AddFriend(const CMD4Hash& userhash, uint32 lastUsedIP, uint32 lastUsedPort, const wxString& name)
{
	CECPacket req(EC_OP_FRIEND);

	CECEmptyTag addtag(EC_TAG_FRIEND_ADD);
	addtag.AddTag(CECTag(EC_TAG_FRIEND_HASH, userhash));
	addtag.AddTag(CECTag(EC_TAG_FRIEND_IP, lastUsedIP));
	addtag.AddTag(CECTag(EC_TAG_FRIEND_PORT, lastUsedPort));
	addtag.AddTag(CECTag(EC_TAG_FRIEND_NAME, name));
	req.AddTag(addtag);

	m_conn->SendPacket(&req);
}
