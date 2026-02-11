GetConnectedHost(void) const
{
	if (ourFCMGuid==0)
		return UNASSIGNED_RAKNET_GUID;
	return hostRakNetGuid;
}
