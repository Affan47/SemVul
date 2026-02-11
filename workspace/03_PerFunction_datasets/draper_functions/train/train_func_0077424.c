AlterObjectNamespace(Relation rel, int oidCacheId, int nameCacheId,
					 Oid objid, Oid nspOid,
					 int Anum_name, int Anum_namespace, int Anum_owner,
					 AclObjectKind acl_kind)
{
	Oid			classId = RelationGetRelid(rel);
	Oid			oldNspOid;
	Datum		name,
				namespace;
	bool		isnull;
	HeapTuple	tup,
				newtup;
	Datum	   *values;
	bool	   *nulls;
	bool	   *replaces;

	tup = SearchSysCacheCopy1(oidCacheId, ObjectIdGetDatum(objid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for object %u of catalog \"%s\"",
			 objid, RelationGetRelationName(rel));

	name = heap_getattr(tup, Anum_name, RelationGetDescr(rel), &isnull);
	Assert(!isnull);
	namespace = heap_getattr(tup, Anum_namespace, RelationGetDescr(rel), &isnull);
	Assert(!isnull);
	oldNspOid = DatumGetObjectId(namespace);


	CheckSetNamespace(oldNspOid, nspOid, classId, objid);


	if (!superuser())
	{
		Datum		owner;
		Oid			ownerId;
		AclResult	aclresult;


		if (Anum_owner <= 0)
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 (errmsg("must be superuser to set schema of %s",
							 getObjectDescriptionOids(classId, objid)))));


		owner = heap_getattr(tup, Anum_owner, RelationGetDescr(rel), &isnull);
		Assert(!isnull);
		ownerId = DatumGetObjectId(owner);

		if (!has_privs_of_role(GetUserId(), ownerId))
			aclcheck_error(ACLCHECK_NOT_OWNER, acl_kind,
						   NameStr(*(DatumGetName(name))));


		aclresult = pg_namespace_aclcheck(nspOid, GetUserId(), ACL_CREATE);
		if (aclresult != ACLCHECK_OK)
			aclcheck_error(aclresult, ACL_KIND_NAMESPACE,
						   get_namespace_name(nspOid));
	}


	if (nameCacheId >= 0 &&
		SearchSysCacheExists2(nameCacheId, name, ObjectIdGetDatum(nspOid)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("%s already exists in schema \"%s\"",
						getObjectDescriptionOids(classId, objid),
						get_namespace_name(nspOid))));


	values = palloc0(RelationGetNumberOfAttributes(rel) * sizeof(Datum));
	nulls = palloc0(RelationGetNumberOfAttributes(rel) * sizeof(bool));
	replaces = palloc0(RelationGetNumberOfAttributes(rel) * sizeof(bool));
	values[Anum_namespace - 1] = ObjectIdGetDatum(nspOid);
	replaces[Anum_namespace - 1] = true;
	newtup = heap_modify_tuple(tup, RelationGetDescr(rel),
							   values, nulls, replaces);


	simple_heap_update(rel, &tup->t_self, newtup);
	CatalogUpdateIndexes(rel, newtup);


	pfree(values);
	pfree(nulls);
	pfree(replaces);


	changeDependencyFor(classId, objid,
						NamespaceRelationId, oldNspOid, nspOid);

	return oldNspOid;
}
