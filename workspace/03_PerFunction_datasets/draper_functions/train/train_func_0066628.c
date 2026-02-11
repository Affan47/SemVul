OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;


	unsigned int i=0;
	while (i < outgoingChallenges.Size())
	{
		if ((rakNetGUID!=UNASSIGNED_RAKNET_GUID && outgoingChallenges[i].remoteSystem.rakNetGuid==rakNetGUID) ||
			(systemAddress!=UNASSIGNED_SYSTEM_ADDRESS && outgoingChallenges[i].remoteSystem.systemAddress==systemAddress))
		{
			outgoingChallenges.RemoveAtIndex(i);
		}
		else
		{
			i++;
		}
	}

	if (rakNetGUID!=UNASSIGNED_RAKNET_GUID)
		nonceGenerator.ClearByAddress(rakNetGUID);
	else
		nonceGenerator.ClearByAddress(systemAddress);
}
