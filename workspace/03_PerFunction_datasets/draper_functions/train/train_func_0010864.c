BroadcastToParticipants(unsigned char *data, const int length, RakNetGUID exclusionGuid)
{
	for (unsigned int i=0; i < participants.Size(); i++)
	{
		if (participants[i]==exclusionGuid)
			continue;
		teamManager->SendUnified((const char*) data, length, HIGH_PRIORITY, RELIABLE_ORDERED, 0, participants[i], false);
	}
}
