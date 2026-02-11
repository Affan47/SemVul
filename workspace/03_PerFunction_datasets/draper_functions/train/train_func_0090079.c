AlterTypeNamespaceInternal(Oid typeOid, Oid nspOid,
						   bool errorOnTableType)
{
	Relation	rel;
	HeapTuple	tup;
	Form_pg_type typform;
	Oid			oldNspOid;
	bool		isCompositeType;

	rel = heap_open(TypeRelationId, RowExclusiveLock);

	tup = SearchSysCacheCopy(TYPEOID,
							 ObjectIdGetDatum(typeOid),
							 0, 0, 0);
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", typeOid);
	typform = (Form_pg_type) GETSTRUCT(tup);

	oldNspOid = typform->typnamespace;

	if (oldNspOid == nspOid)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("type %s is already in schema \"%s\"",
						format_type_be(typeOid),
						get_namespace_name(nspOid))));


	if (isAnyTempNamespace(nspOid) || isAnyTempNamespace(oldNspOid))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
			errmsg("cannot move objects into or out of temporary schemas")));


	if (nspOid == PG_TOAST_NAMESPACE || oldNspOid == PG_TOAST_NAMESPACE)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot move objects into or out of TOAST schema")));


	if (SearchSysCacheExists(TYPENAMENSP,
							 CStringGetDatum(NameStr(typform->typname)),
							 ObjectIdGetDatum(nspOid),
							 0, 0))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("type \"%s\" already exists in schema \"%s\"",
						NameStr(typform->typname),
						get_namespace_name(nspOid))));


	isCompositeType =
		(typform->typtype == 'c' &&
		 get_rel_relkind(typform->typrelid) == RELKIND_COMPOSITE_TYPE);


	if (typform->typtype == 'c' && !isCompositeType && errorOnTableType)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("%s is a table's row type",
						format_type_be(typeOid)),
				 errhint("Use ALTER TABLE SET SCHEMA instead.")));


	typform->typnamespace = nspOid;

	simple_heap_update(rel, &tup->t_self, tup);
	CatalogUpdateIndexes(rel, tup);


	if (isCompositeType)
	{
		Relation	classRel;

		classRel = heap_open(RelationRelationId, RowExclusiveLock);


		AlterRelationNamespaceInternal(classRel, typform->typrelid,
									   oldNspOid, nspOid,
									   true);

		heap_close(classRel, RowExclusiveLock);


		AlterConstraintNamespaces(typform->typrelid, oldNspOid,
								  nspOid, false);
	}
	else
	{

		if (typform->typtype == 'd')
			AlterConstraintNamespaces(typeOid, oldNspOid, nspOid, true);


		if (typform->typtype != 'c')
			if (changeDependencyFor(TypeRelationId, typeOid,
								NamespaceRelationId, oldNspOid, nspOid) != 1)
				elog(ERROR, "failed to change schema dependency for type %s",
					 format_type_be(typeOid));
	}

	heap_freetuple(tup);

	heap_close(rel, RowExclusiveLock);
}
