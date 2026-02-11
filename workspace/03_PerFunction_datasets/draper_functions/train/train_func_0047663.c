PortalStart(Portal portal, ParamListInfo params, Snapshot snapshot)
{
	Portal		saveActivePortal;
	ResourceOwner saveResourceOwner;
	MemoryContext savePortalContext;
	MemoryContext oldContext;
	QueryDesc  *queryDesc;
	int			eflags;

	AssertArg(PortalIsValid(portal));
	AssertState(portal->status == PORTAL_DEFINED);


	saveActivePortal = ActivePortal;
	saveResourceOwner = CurrentResourceOwner;
	savePortalContext = PortalContext;
	PG_TRY();
	{
		ActivePortal = portal;
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
											false);


				if (portal->cursorOptions & CURSOR_OPT_SCROLL)
					eflags = EXEC_FLAG_REWIND | EXEC_FLAG_BACKWARD;
				else
					eflags = 0;


				ExecutorStart(queryDesc, eflags);


				portal->queryDesc = queryDesc;


				portal->tupDesc = queryDesc->tupDesc;


				portal->atStart = true;
				portal->atEnd = false;
				portal->portalPos = 0;
				portal->posOverflow = false;

				PopActiveSnapshot();
				break;

			case PORTAL_ONE_RETURNING:


				{
					PlannedStmt *pstmt;

					pstmt = (PlannedStmt *) PortalGetPrimaryStmt(portal);
					Assert(IsA(pstmt, PlannedStmt));
					Assert(pstmt->returningLists);
					portal->tupDesc =
						ExecCleanTypeFromTL((List *) linitial(pstmt->returningLists),
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

		portal->status = PORTAL_FAILED;


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
