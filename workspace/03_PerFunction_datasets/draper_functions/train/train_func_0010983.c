LockTableRecurse(Oid reloid, RangeVar *rv,
				 LOCKMODE lockmode, bool nowait, bool recurse)
{
	Relation	rel;
	AclResult	aclresult;


	if (nowait)
	{
		if (!ConditionalLockRelationOid(reloid, lockmode))
		{

			char	   *relname = rv ? rv->relname : get_rel_name(reloid);

			if (relname)
				ereport(ERROR,
						(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
						 errmsg("could not obtain lock on relation \"%s\"",
								relname)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
					  errmsg("could not obtain lock on relation with OID %u",
							 reloid)));
		}
	}
	else
		LockRelationOid(reloid, lockmode);


	rel = try_relation_open(reloid, NoLock);

	if (!rel)
	{

		UnlockRelationOid(reloid, lockmode);


		if (rv)
		{
			if (rv->schemaname)
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_TABLE),
						 errmsg("relation \"%s.%s\" does not exist",
								rv->schemaname, rv->relname)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_TABLE),
						 errmsg("relation \"%s\" does not exist",
								rv->relname)));
		}

		return;
	}


	if (lockmode == AccessShareLock)
		aclresult = pg_class_aclcheck(reloid, GetUserId(),
									  ACL_SELECT);
	else
		aclresult = pg_class_aclcheck(reloid, GetUserId(),
									  ACL_UPDATE | ACL_DELETE | ACL_TRUNCATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, ACL_KIND_CLASS,
					   RelationGetRelationName(rel));


	if (rel->rd_rel->relkind != RELKIND_RELATION)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("\"%s\" is not a table",
						RelationGetRelationName(rel))));


	if (recurse)
	{
		List	   *children = find_inheritance_children(reloid, NoLock);
		ListCell   *lc;

		foreach(lc, children)
		{
			Oid			childreloid = lfirst_oid(lc);

			LockTableRecurse(childreloid, NULL, lockmode, nowait, recurse);
		}
	}

	relation_close(rel, NoLock);
}
