ExecOpenScanRelation(EState *estate, Index scanrelid)
{
	Oid			reloid;
	LOCKMODE	lockmode;


	lockmode = AccessShareLock;
	if (ExecRelationIsTargetRelation(estate, scanrelid))
		lockmode = NoLock;
	else
	{
		ListCell   *l;

		foreach(l, estate->es_rowMarks)
		{
			ExecRowMark *erm = lfirst(l);

			if (erm->rti == scanrelid)
			{
				lockmode = NoLock;
				break;
			}
		}
	}


	reloid = getrelid(scanrelid, estate->es_range_table);
	return heap_open(reloid, lockmode);
}
