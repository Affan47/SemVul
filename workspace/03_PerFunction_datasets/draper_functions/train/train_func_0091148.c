PortalStart(Portal portal, ParamListInfo params,
			int eflags, Snapshot snapshot)
{
	Portal		saveActivePortal;
	ResourceOwner saveResourceOwner;
	MemoryContext savePortalContext;
	MemoryContext oldContext;
	QueryDesc  *queryDesc;
	int			myeflags;

	AssertArg(PortalIsValid(portal));
	AssertState(portal->status == PORTAL_DEFINED);


	saveActivePortal = ActivePortal;
	saveResourceOwner = CurrentResourceOwner;
	savePortalContext = PortalContext;
	PG_TRY();
	{
		ActivePortal = portal;
		if (portal->resowner)
			CurrentResourceOwner = portal->resowner;
		PortalContext = PortalGetHeapMemory(portal);

		oldContext = MemoryContextSwitchTo(PortalGetHeapMemory(portal));


		portal->portalParams = params;


		portal->strategy = ChoosePortalStrategy(portal->stmts);


		switch (portal->strategy)
		{
			case PORTAL_ONE_SELECT:


				if (snapshot)
					PushActiveSnapshot(snapshot);
				else
					PushActiveSnapshot(GetTransactionSnapshot());


				queryDesc = CreateQueryDesc((PlannedStmt *) linitial(portal->stmts),
											portal->sourceText,
											GetActiveSnapshot(),
											InvalidSnapshot,
											None_Receiver,
											params,
											0);


				if (portal->cursorOptions & CURSOR_OPT_SCROLL)
					myeflags = eflags | EXEC_FLAG_REWIND | EXEC_FLAG_BACKWARD;
				else
					myeflags = eflags;


				ExecutorStart(queryDesc, myeflags);


				portal->queryDesc = queryDesc;


				portal->tupDesc = queryDesc->tupDesc;


				portal->atStart = true;
				portal->atEnd = false;
				portal->portalPos = 0;
				portal->posOverflow = false;

				PopActiveSnapshot();
				break;

			case PORTAL_ONE_RETURNING:
			case PORTAL_ONE_MOD_WITH:


				{
					PlannedStmt *pstmt;

					pstmt = (PlannedStmt *) PortalGetPrimaryStmt(portal);
					Assert(IsA(pstmt, PlannedStmt));
					portal->tupDesc =
						ExecCleanTypeFromTL(pstmt->planTree->targetlist,
											false);
				}


				portal->atStart = true;
				portal->atEnd = false;
				portal->portalPos = 0;
				portal->posOverflow = false;
				break;

			case PORTAL_UTIL_SELECT:


				{
					Node	   *ustmt = PortalGetPrimaryStmt(portal);

					Assert(!IsA(ustmt, PlannedStmt));
					portal->tupDesc = UtilityTupleDescriptor(ustmt);
				}


				portal->atStart = true;
				portal->atEnd = false;
				portal->portalPos = 0;
				portal->posOverflow = false;
				break;

			case PORTAL_MULTI_QUERY:

				portal->tupDesc = NULL;
				break;
		}
	}
	PG_CATCH();
	{

		MarkPortalFailed(portal);


		ActivePortal = saveActivePortal;
		CurrentResourceOwner = saveResourceOwner;
		PortalContext = savePortalContext;

		PG_RE_THROW();
	}
	PG_END_TRY();

	MemoryContextSwitchTo(oldContext);

	ActivePortal = saveActivePortal;
	CurrentResourceOwner = saveResourceOwner;
	PortalContext = savePortalContext;

	portal->status = PORTAL_READY;
}
