relation_open_nowait(Oid relationId, LOCKMODE lockmode)
{
	Relation	r;

	Assert(lockmode >= NoLock && lockmode < MAX_LOCKMODES);


	if (lockmode != NoLock)
	{
		if (!ConditionalLockRelationOid(relationId, lockmode))
		{

			char	   *relname = get_rel_name(relationId);

			if (relname)
				ereport(ERROR,
						(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
						 errmsg("could not obtain lock on relation \"%s\"",
								relname)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
					  errmsg("could not obtain lock on relation with OID %u",
							 relationId)));
		}
	}


	r = RelationIdGetRelation(relationId);

	if (!RelationIsValid(r))
		elog(ERROR, "could not open relation with OID %u", relationId);


	if (r->rd_istemp)
		MyXactAccessedTempRel = true;

	pgstat_initstats(r);

	return r;
}
