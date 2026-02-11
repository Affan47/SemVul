GetRemoteSystemFromSystemAddress( const SystemAddress systemAddress, bool calledFromNetworkThread, bool onlyActive ) const
{
	unsigned i;

	if ( systemAddress == UNASSIGNED_SYSTEM_ADDRESS )
		return 0;

	if (calledFromNetworkThread)
	{
		unsigned int index = GetRemoteSystemIndex(systemAddress);
		if (index!=(unsigned int) -1)
		{
			if (onlyActive==false || remoteSystemList[ index ].isActive==true )
			{
				RakAssert(remoteSystemList[index].systemAddress==systemAddress);
				return remoteSystemList + index;
			}
		}
	}
	else
	{
		int deadConnectionIndex=-1;


		for ( i = 0; i < maximumNumberOfPeers; i++ )
		{
			if (remoteSystemList[ i ].systemAddress == systemAddress)
			{
				if ( remoteSystemList[ i ].isActive )
					return remoteSystemList + i;
				else if (deadConnectionIndex==-1)
					deadConnectionIndex=i;
			}
		}

		if (deadConnectionIndex!=-1 && onlyActive==false)
			return remoteSystemList + deadConnectionIndex;
	}

	return 0;
}
