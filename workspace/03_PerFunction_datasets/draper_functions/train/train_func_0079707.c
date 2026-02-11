AlterSchemaOwner_internal(HeapTuple tup, Relation rel, Oid newOwnerId)
{
	Form_pg_namespace nspForm;

	Assert(tup->t_tableOid == NamespaceRelationId);
	Assert(RelationGetRelid(rel) == NamespaceRelationId);

	nspForm = (Form_pg_namespace) GETSTRUCT(tup);


	if (nspForm->nspowner != newOwnerId)
	{
		Datum		repl_val[Natts_pg_namespace];
		char		repl_null[Natts_pg_namespace];
		char		repl_repl[Natts_pg_namespace];
		Acl		   *newAcl;
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	newtuple;
		AclResult	aclresult;


		if (!pg_namespace_ownercheck(HeapTupleGetOid(tup), GetUserId()))
			aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_NAMESPACE,
						   NameStr(nspForm->nspname));


		check_is_member_of_role(GetUserId(), newOwnerId);


		aclresult = pg_database_aclcheck(MyDatabaseId, GetUserId(),
										 ACL_CREATE);
		if (aclresult != ACLCHECK_OK)
			aclcheck_error(aclresult, ACL_KIND_DATABASE,
						   get_database_name(MyDatabaseId));

		memset(repl_null, ' ', sizeof(repl_null));
		memset(repl_repl, ' ', sizeof(repl_repl));

		repl_repl[Anum_pg_namespace_nspowner - 1] = 'r';
		repl_val[Anum_pg_namespace_nspowner - 1] = ObjectIdGetDatum(newOwnerId);


		aclDatum = SysCacheGetAttr(NAMESPACENAME, tup,
								   Anum_pg_namespace_nspacl,
								   &isNull);
		if (!isNull)
		{
			newAcl = aclnewowner(DatumGetAclP(aclDatum),
								 nspForm->nspowner, newOwnerId);
			repl_repl[Anum_pg_namespace_nspacl - 1] = 'r';
			repl_val[Anum_pg_namespace_nspacl - 1] = PointerGetDatum(newAcl);
		}

		newtuple = heap_modifytuple(tup, RelationGetDescr(rel), repl_val, repl_null, repl_repl);

		simple_heap_update(rel, &newtuple->t_self, newtuple);
		CatalogUpdateIndexes(rel, newtuple);

		heap_freetuple(newtuple);


		changeDependencyOnOwner(NamespaceRelationId, HeapTupleGetOid(tup),
								newOwnerId);
	}

}
