PortalRunUtility(Portal portal, Query *query,
				 DestReceiver *dest, char *completionTag)
{
	Node	   *utilityStmt = query->utilityStmt;

	ereport(DEBUG3,
			(errmsg_internal("ProcessUtility")));


	if (!(IsA(utilityStmt, TransactionStmt) ||
		  IsA(utilityStmt, LockStmt) ||
		  IsA(utilityStmt, VariableSetStmt) ||
		  IsA(utilityStmt, VariableShowStmt) ||
		  IsA(utilityStmt, VariableResetStmt) ||
		  IsA(utilityStmt, ConstraintsSetStmt) ||

		  IsA(utilityStmt, FetchStmt) ||
		  IsA(utilityStmt, ListenStmt) ||
		  IsA(utilityStmt, NotifyStmt) ||
		  IsA(utilityStmt, UnlistenStmt) ||
		  IsA(utilityStmt, CheckPointStmt)))
		ActiveSnapshot = CopySnapshot(GetTransactionSnapshot());
	else
		ActiveSnapshot = NULL;

	if (query->canSetTag)
	{

		ProcessUtility(utilityStmt, portal->portalParams, dest, completionTag);
		if (completionTag && completionTag[0] == '\0' && portal->commandTag)
			strcpy(completionTag, portal->commandTag);
	}
	else
	{

		ProcessUtility(utilityStmt, portal->portalParams, dest, NULL);
	}


	MemoryContextSwitchTo(PortalGetHeapMemory(portal));

	if (ActiveSnapshot)
		FreeSnapshot(ActiveSnapshot);
	ActiveSnapshot = NULL;
}
