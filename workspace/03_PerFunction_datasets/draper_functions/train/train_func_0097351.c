AddParticipant(const SystemAddress &systemAddress, RakNetGUID rakNetGUID)
{

	RakNet::BitStream bs;
	bs.Write((MessageID)ID_REMOTE_NEW_INCOMING_CONNECTION);
	bs.Write((uint32_t)1);
	bs.Write(systemAddress);
	bs.Write(rakNetGUID);
	bs.WriteCasted<uint16_t>(rakPeerInterface->GetAveragePing(rakNetGUID));
	SendUnified(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,systemAddress,true);


	DataStructures::List<SystemAddress> addresses;
	DataStructures::List<RakNetGUID> guids;
	rakPeerInterface->GetSystemList(addresses, guids);
	bs.Reset();
	bs.Write((MessageID)ID_REMOTE_NEW_INCOMING_CONNECTION);
	BitSize_t writeOffset = bs.GetWriteOffset();
	bs.Write((uint32_t) addresses.Size());

	unsigned int i;
	uint32_t count=0;
	for (i=0; i < addresses.Size(); i++)
	{
		if (addresses[i]==systemAddress)
			continue;

		bs.Write(addresses[i]);
		bs.Write(guids[i]);
		bs.WriteCasted<uint16_t>(rakPeerInterface->GetAveragePing(guids[i]));
		count++;
	}

	if (count>0)
	{
		BitSize_t writeOffset2 = bs.GetWriteOffset();
		bs.SetWriteOffset(writeOffset);
		bs.Write(count);
		bs.SetWriteOffset(writeOffset2);
		SendUnified(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,systemAddress,false);
	}

	bool objectExists;
	unsigned int ii = remoteSystems.GetIndexFromKey(rakNetGUID, &objectExists);
	if (objectExists==false)
	{
		RemoteSystem* remoteSystem = RakNet::OP_NEW<RemoteSystem>(_FILE_AND_LINE_);
		remoteSystem->guid=rakNetGUID;
		remoteSystems.InsertAtIndex(remoteSystem,ii,_FILE_AND_LINE_);
	}
}
