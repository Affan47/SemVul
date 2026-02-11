try_relation_open(Oid relationId, LOCKMODE lockmode)
{
	Relation	r;

	Assert(lockmode >= NoLock && lockmode < MAX_LOCKMODES);


	if (lockmode != NoLock)
		LockRelationOid(relationId, lockmode);


	if (!SearchSysCacheExists(RELOID,
							  ObjectIdGetDatum(relationId),
							  0, 0, 0))
	{

		if (lockmode != NoLock)
			UnlockRelationOid(relationId, lockmode);

		return NULL;
	}


	r = RelationIdGetRelation(relationId);

	if (!RelationIsValid(r))
		elog(ERROR, "could not open relation with OID %u", relationId);


	if (r->rd_istemp)
		MyXactAccessedTempRel = true;

	return r;
}
