HasParticipant(RakNetGUID participantGuid)
{
	unsigned int i;
	for (i=0; i < fcm2ParticipantList.Size(); i++)
	{
		if (fcm2ParticipantList[i]->rakNetGuid==participantGuid)
			return true;
	}
	return false;
}
