HasCompletedConnectionAttempt(void)
{
	SystemAddress sysAddr=UNASSIGNED_SYSTEM_ADDRESS;
	completedConnectionAttemptMutex.Lock();
	if (completedConnectionAttempts.IsEmpty()==false)
		sysAddr=completedConnectionAttempts.Pop();
	completedConnectionAttemptMutex.Unlock();

	if (sysAddr!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		unsigned int i;
		for (i=0; i < messageHandlerList.Size(); i++)
			messageHandlerList[i]->OnNewConnection(sysAddr, UNASSIGNED_RAKNET_GUID, true);
	}

	return sysAddr;
}
