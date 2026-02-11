AlterObjectNamespace(Relation rel, int cacheId,
					 Oid classId, Oid objid, Oid nspOid,
					 int Anum_name, int Anum_namespace, int Anum_owner,
					 AclObjectKind acl_kind,
					 bool superuser_only)
{
	Oid			oldNspOid;
	Datum       name, namespace;
	bool        isnull;
	HeapTuple	tup, newtup = NULL;
	Datum	   *values;
	bool	   *nulls;
	bool	   *replaces;

	tup = SearchSysCacheCopy1(cacheId, ObjectIdGetDatum(objid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for object %u: %s",
			 objid, getObjectDescriptionOids(classId, objid));

	name = heap_getattr(tup, Anum_name, rel->rd_att, &isnull);
	namespace = heap_getattr(tup, Anum_namespace, rel->rd_att, &isnull);
	oldNspOid = DatumGetObjectId(namespace);


	CheckSetNamespace(oldNspOid, nspOid, classId, objid);


	if (SearchSysCacheExists2(cacheId, name, ObjectIdGetDatum(nspOid)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("%s already exists in schema \"%s\"",
						getObjectDescriptionOids(classId, objid),
						get_namespace_name(nspOid))));


	if (!superuser())
	{
		Datum       owner;
		Oid			ownerId;
		AclResult	aclresult;

		if (superuser_only)
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 (errmsg("must be superuser to SET SCHEMA of %s",
							 getObjectDescriptionOids(classId, objid)))));


		owner = heap_getattr(tup, Anum_owner, rel->rd_att, &isnull);
		ownerId = DatumGetObjectId(owner);

		if (!has_privs_of_role(GetUserId(), ownerId))
			aclcheck_error(ACLCHECK_NOT_OWNER, acl_kind,
						   NameStr(*(DatumGetName(name))));


		aclresult = pg_namespace_aclcheck(oldNspOid, GetUserId(), ACL_CREATE);
		if (aclresult != ACLCHECK_OK)
			aclcheck_error(aclresult, ACL_KIND_NAMESPACE,
						   get_namespace_name(oldNspOid));
	}


	values = palloc0(rel->rd_att->natts * sizeof(Datum));
	nulls = palloc0(rel->rd_att->natts * sizeof(bool));
	replaces = palloc0(rel->rd_att->natts * sizeof(bool));
	values[Anum_namespace - 1] = nspOid;
	replaces[Anum_namespace - 1] = true;
	newtup = heap_modify_tuple(tup, rel->rd_att, values, nulls, replaces);


	simple_heap_update(rel, &tup->t_self, newtup);
	CatalogUpdateIndexes(rel, newtup);


	pfree(values);
	pfree(nulls);
	pfree(replaces);


	changeDependencyFor(classId, objid,
						NamespaceRelationId, oldNspOid, nspOid);
}
