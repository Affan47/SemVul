OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
	(void) isIncoming;
	(void) systemAddress;

	if (autoAddParticipants)
		AddParticipant(rakNetGUID);
}
