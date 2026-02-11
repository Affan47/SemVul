SetTimeoutTime( RakNet::TimeMS timeMS, const SystemAddress target )
{
	if (target==UNASSIGNED_SYSTEM_ADDRESS)
	{
		defaultTimeoutTime=timeMS;

		unsigned i;
		for ( i = 0; i < maximumNumberOfPeers; i++ )
		{
			if (remoteSystemList[ i ].isActive)
			{
				if ( remoteSystemList[ i ].isActive )
					remoteSystemList[ i ].reliabilityLayer.SetTimeoutTime(timeMS);
			}
		}
	}
	else
	{
		RemoteSystemStruct * remoteSystem = GetRemoteSystemFromSystemAddress( target, false, true );

		if ( remoteSystem != 0 )
			remoteSystem->reliabilityLayer.SetTimeoutTime(timeMS);
	}
}
