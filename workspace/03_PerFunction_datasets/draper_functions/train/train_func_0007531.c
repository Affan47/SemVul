AddParticipant( RakNetGUID rakNetGuid )
{
	if (rakPeerInterface->GetConnectionState(rakPeerInterface->GetSystemAddressFromGuid(rakNetGuid))!=IS_CONNECTED)
	{
#ifdef DEBUG_FCM2
		printf("AddParticipant to %s failed (not connected)\n", rakNetGuid.ToString());
#endif
		return;
	}


	AddParticipantInternal(rakNetGuid,0);
}
