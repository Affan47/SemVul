RemoveOperator(RemoveFuncStmt *stmt)
{
	List	   *operatorName = stmt->name;
	TypeName   *typeName1 = (TypeName *) linitial(stmt->args);
	TypeName   *typeName2 = (TypeName *) lsecond(stmt->args);
	Oid			operOid;
	HeapTuple	tup;
	ObjectAddress object;

	Assert(list_length(stmt->args) == 2);
	operOid = LookupOperNameTypeNames(NULL, operatorName,
									  typeName1, typeName2,
									  stmt->missing_ok, -1);

	if (stmt->missing_ok && !OidIsValid(operOid))
	{
		ereport(NOTICE,
				(errmsg("operator %s does not exist, skipping",
						NameListToString(operatorName))));
		return;
	}

	tup = SearchSysCache(OPEROID,
						 ObjectIdGetDatum(operOid),
						 0, 0, 0);
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for operator %u", operOid);


	if (!pg_oper_ownercheck(operOid, GetUserId()) &&
		!pg_namespace_ownercheck(((Form_pg_operator) GETSTRUCT(tup))->oprnamespace,
								 GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_OPER,
					   NameListToString(operatorName));

	ReleaseSysCache(tup);


	object.classId = OperatorRelationId;
	object.objectId = operOid;
	object.objectSubId = 0;

	performDeletion(&object, stmt->behavior);
}
