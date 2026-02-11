RenameOpClass(List *name, const char *access_method, const char *newname)
{
	Oid			opcOid;
	Oid			amOid;
	Oid			namespaceOid;
	HeapTuple	origtup;
	HeapTuple	tup;
	Relation	rel;
	AclResult	aclresult;

	amOid = get_am_oid(access_method, false);

	rel = heap_open(OperatorClassRelationId, RowExclusiveLock);


	origtup = OpClassCacheLookup(amOid, name, false);
	tup = heap_copytuple(origtup);
	ReleaseSysCache(origtup);
	opcOid = HeapTupleGetOid(tup);
	namespaceOid = ((Form_pg_opclass) GETSTRUCT(tup))->opcnamespace;


	if (SearchSysCacheExists3(CLAAMNAMENSP,
							  ObjectIdGetDatum(amOid),
							  CStringGetDatum(newname),
							  ObjectIdGetDatum(namespaceOid)))
	{
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("operator class \"%s\" for access method \"%s\" already exists in schema \"%s\"",
						newname, access_method,
						get_namespace_name(namespaceOid))));
	}


	if (!pg_opclass_ownercheck(opcOid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_OPCLASS,
					   NameListToString(name));


	aclresult = pg_namespace_aclcheck(namespaceOid, GetUserId(), ACL_CREATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, ACL_KIND_NAMESPACE,
					   get_namespace_name(namespaceOid));


	namestrcpy(&(((Form_pg_opclass) GETSTRUCT(tup))->opcname), newname);
	simple_heap_update(rel, &tup->t_self, tup);
	CatalogUpdateIndexes(rel, tup);

	heap_close(rel, NoLock);
	heap_freetuple(tup);
}
