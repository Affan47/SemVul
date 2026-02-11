OnVerifiedJoinAccepted(Packet *packet)
{
	RakNet::BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	RakNetGUID systemToAddGuid;
	bsIn.Read(systemToAddGuid);

	if (systemToAddGuid==rakPeerInterface->GetMyGUID())
	{

		unsigned int curIndex = GetJoinsInProgressIndex(packet->guid);
		if (curIndex==(unsigned int)-1)
			return;

		unsigned short listSize;
		bsIn.Read(listSize);
		for (unsigned short i=0; i < listSize; i++)
		{

			RakNetGUID guid;
			bsIn.Read(guid);
			rakPeerInterface->CloseConnection(guid, true);
		}

		bsIn.Read(listSize);
		for (unsigned short i=0; i < listSize; i++)
		{

			RakNetGUID guid;
			bsIn.Read(guid);
			AddParticipant(guid);
		}
		AddParticipant(packet->guid);

		for (unsigned int j=0; j < joinsInProgress[curIndex]->vjipMembers.Size(); j++)
		{
			if ( joinsInProgress[curIndex]->vjipMembers[j].userData != 0)
			{
				RakNet::OP_DELETE(joinsInProgress[curIndex]->vjipMembers[j].userData, _FILE_AND_LINE_);
			}
		}


		RakNet::OP_DELETE(joinsInProgress[curIndex], _FILE_AND_LINE_);
		joinsInProgress.RemoveAtIndex(curIndex);
	}
	else
	{

		ConnectionState cs = rakPeerInterface->GetConnectionState(systemToAddGuid);
		RakAssert(cs==IS_CONNECTED);
		if (cs==IS_CONNECTED)
			AddParticipant(systemToAddGuid);
	}
}
