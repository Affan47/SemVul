AllRemoteServersHaveResponded(void) const
{
	unsigned int i;
	for (i=0; i < remoteServerResponses.Size(); i++)
		if (remoteServerResponses[i]->gotResult==false)
			return false;
	return true;
}
