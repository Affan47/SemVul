AcquireExecutorLocks(List *stmt_list, bool acquire)
{
	ListCell   *lc1;

	foreach(lc1, stmt_list)
	{
		PlannedStmt *plannedstmt = (PlannedStmt *) lfirst(lc1);
		int			rt_index;
		ListCell   *lc2;

		Assert(!IsA(plannedstmt, Query));
		if (!IsA(plannedstmt, PlannedStmt))
			continue;

		rt_index = 0;
		foreach(lc2, plannedstmt->rtable)
		{
			RangeTblEntry *rte = (RangeTblEntry *) lfirst(lc2);
			LOCKMODE	lockmode;

			rt_index++;

			if (rte->rtekind != RTE_RELATION)
				continue;


			if (list_member_int(plannedstmt->resultRelations, rt_index))
				lockmode = RowExclusiveLock;
			else if (rowmark_member(plannedstmt->rowMarks, rt_index))
				lockmode = RowShareLock;
			else
				lockmode = AccessShareLock;

			if (acquire)
				LockRelationOid(rte->relid, lockmode);
			else
				UnlockRelationOid(rte->relid, lockmode);
		}
	}
}
