GetClockDifferential( const AddressOrGUID systemIdentifier )
{
	RemoteSystemStruct *remoteSystem = GetRemoteSystem(systemIdentifier, false, false);
	if (remoteSystem == 0)
		return 0;
	return GetClockDifferentialInt(remoteSystem);
}
