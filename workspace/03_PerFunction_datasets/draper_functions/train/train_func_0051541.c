OnVerifiedJoinCapable(Packet *packet)
{
	VerifiedJoinInProgress vjip;
	DecomposeJoinCapable(packet, &vjip);


	RakAssert(HasParticipant(packet->guid)==false);

	DataStructures::List<RakNetGUID> participatingMembersOnClientSucceeded;
	DataStructures::List<RakNetGUID> participatingMembersOnClientFailed;
	DataStructures::List<RakNetGUID> participatingMembersNotOnClient;
	DataStructures::List<RakNetGUID> clientMembersNotParticipatingSucceeded;
	DataStructures::List<RakNetGUID> clientMembersNotParticipatingFailed;
	CategorizeVJIP(&vjip,
		participatingMembersOnClientSucceeded,
		participatingMembersOnClientFailed,
		participatingMembersNotOnClient,
		clientMembersNotParticipatingSucceeded,
		clientMembersNotParticipatingFailed);

	if (participatingMembersOnClientFailed.Size()>0)
	{

		BitStream bsOut;
		bsOut.Write((MessageID) ID_FCM2_VERIFIED_JOIN_FAILED);
		SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}

	if (participatingMembersNotOnClient.Size()>0)
	{
		BitStream bsOut;
		bsOut.Write((MessageID) ID_FCM2_VERIFIED_JOIN_START);
		bsOut.WriteCasted<unsigned short>(participatingMembersNotOnClient.Size());
		unsigned int i;
		for (i=0; i < participatingMembersNotOnClient.Size(); i++)
		{
			bsOut.Write(participatingMembersNotOnClient[i]);
			bsOut.Write(rakPeerInterface->GetSystemAddressFromGuid(participatingMembersNotOnClient[i]));

			bool written=false;
			for (unsigned int j=0; j < fcm2ParticipantList.Size(); j++)
			{
				if (fcm2ParticipantList[j]->rakNetGuid == participatingMembersNotOnClient[i])
				{
					written=true;

					BitStream vjsOut;

					WriteVJSUserData(&vjsOut, fcm2ParticipantList[j]->rakNetGuid );
					bsOut.Write(vjsOut.GetNumberOfBitsUsed());
					bsOut.Write(&vjsOut);
					bsOut.AlignWriteToByteBoundary();
					break;
				}
			}
			RakAssert(written);
		}
		SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}


	return RR_CONTINUE_PROCESSING;
}
