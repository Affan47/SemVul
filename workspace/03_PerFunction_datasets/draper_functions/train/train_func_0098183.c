ExecGrant_Language(InternalGrant *istmt)
{
	Relation	relation;
	ListCell   *cell;

	if (istmt->all_privs && istmt->privileges == ACL_NO_RIGHTS)
		istmt->privileges = ACL_ALL_RIGHTS_LANGUAGE;

	relation = heap_open(LanguageRelationId, RowExclusiveLock);

	foreach(cell, istmt->objects)
	{
		Oid			langId = lfirst_oid(cell);
		Form_pg_language pg_language_tuple;
		Datum		aclDatum;
		bool		isNull;
		AclMode		avail_goptions;
		AclMode		this_privileges;
		Acl		   *old_acl;
		Acl		   *new_acl;
		Oid			grantorId;
		Oid			ownerId;
		HeapTuple	tuple;
		HeapTuple	newtuple;
		Datum		values[Natts_pg_language];
		char		nulls[Natts_pg_language];
		char		replaces[Natts_pg_language];
		int			noldmembers;
		int			nnewmembers;
		Oid		   *oldmembers;
		Oid		   *newmembers;

		tuple = SearchSysCache(LANGOID,
							   ObjectIdGetDatum(langId),
							   0, 0, 0);
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for language %u", langId);

		pg_language_tuple = (Form_pg_language) GETSTRUCT(tuple);

		if (!pg_language_tuple->lanpltrusted)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("language \"%s\" is not trusted",
							NameStr(pg_language_tuple->lanname)),
				   errhint("Only superusers may use untrusted languages.")));


		ownerId = BOOTSTRAP_SUPERUSERID;
		aclDatum = SysCacheGetAttr(LANGNAME, tuple, Anum_pg_language_lanacl,
								   &isNull);
		if (isNull)
			old_acl = acldefault(ACL_OBJECT_LANGUAGE, ownerId);
		else
			old_acl = DatumGetAclPCopy(aclDatum);


		select_best_grantor(GetUserId(), istmt->privileges,
							old_acl, ownerId,
							&grantorId, &avail_goptions);


		this_privileges =
			restrict_and_check_grant(istmt->is_grant, avail_goptions,
									 istmt->all_privs, istmt->privileges,
									 langId, grantorId, ACL_KIND_LANGUAGE,
									 NameStr(pg_language_tuple->lanname));


		noldmembers = aclmembers(old_acl, &oldmembers);

		new_acl = merge_acl_with_grant(old_acl, istmt->is_grant,
									   istmt->grant_option, istmt->behavior,
									   istmt->grantees, this_privileges,
									   grantorId, ownerId);

		nnewmembers = aclmembers(new_acl, &newmembers);


		MemSet(values, 0, sizeof(values));
		MemSet(nulls, ' ', sizeof(nulls));
		MemSet(replaces, ' ', sizeof(replaces));

		replaces[Anum_pg_language_lanacl - 1] = 'r';
		values[Anum_pg_language_lanacl - 1] = PointerGetDatum(new_acl);

		newtuple = heap_modifytuple(tuple, RelationGetDescr(relation), values,
									nulls, replaces);

		simple_heap_update(relation, &newtuple->t_self, newtuple);


		CatalogUpdateIndexes(relation, newtuple);


		updateAclDependencies(LanguageRelationId, HeapTupleGetOid(tuple),
							  ownerId, istmt->is_grant,
							  noldmembers, oldmembers,
							  nnewmembers, newmembers);

		ReleaseSysCache(tuple);

		pfree(new_acl);


		CommandCounterIncrement();
	}

	heap_close(relation, RowExclusiveLock);
}
