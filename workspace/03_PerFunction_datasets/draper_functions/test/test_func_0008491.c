GetGroupList(const RakNetGUID &relayPluginServerGuid)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_GET_GROUP_LIST_REQUEST_FROM_CLIENT);
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, relayPluginServerGuid, false);
}
