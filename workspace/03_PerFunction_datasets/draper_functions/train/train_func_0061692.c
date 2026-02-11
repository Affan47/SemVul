GetConnectionList( SystemAddress *remoteSystems, unsigned short *numberOfSystems ) const
{
	unsigned short systemCount=0;
	unsigned short maxToWrite=*numberOfSystems;
	for (int i=0; i < remoteClientsLength; i++)
	{
		if (remoteClients[i].isActive)
		{
			if (systemCount < maxToWrite)
				remoteSystems[systemCount]=remoteClients[i].systemAddress;
			systemCount++;
		}
	}
	*numberOfSystems=systemCount;
}
