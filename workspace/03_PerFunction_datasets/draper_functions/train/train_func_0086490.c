RemoveOpClass(RemoveOpClassStmt *stmt)
{
	Oid			amID,
				opcID;
	HeapTuple	tuple;
	ObjectAddress object;


	amID = GetSysCacheOid(AMNAME,
						  CStringGetDatum(stmt->amname),
						  0, 0, 0);
	if (!OidIsValid(amID))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("access method \"%s\" does not exist",
						stmt->amname)));


	tuple = OpClassCacheLookup(amID, stmt->opclassname);
	if (!HeapTupleIsValid(tuple))
	{
		if (!stmt->missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("operator class \"%s\" does not exist for access method \"%s\"",
						NameListToString(stmt->opclassname), stmt->amname)));
		else
			ereport(NOTICE,
					(errmsg("operator class \"%s\" does not exist for access method \"%s\"",
						NameListToString(stmt->opclassname), stmt->amname)));
		return;
	}

	opcID = HeapTupleGetOid(tuple);


	if (!pg_opclass_ownercheck(opcID, GetUserId()) &&
		!pg_namespace_ownercheck(((Form_pg_opclass) GETSTRUCT(tuple))->opcnamespace,
								 GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_OPCLASS,
					   NameListToString(stmt->opclassname));

	ReleaseSysCache(tuple);


	object.classId = OperatorClassRelationId;
	object.objectId = opcID;
	object.objectSubId = 0;

	performDeletion(&object, stmt->behavior);
}
