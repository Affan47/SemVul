AlterTypeNamespaceInternal(Oid typeOid, Oid nspOid,
						   bool isImplicitArray,
						   bool errorOnTableType)
{
	Relation	rel;
	HeapTuple	tup;
	Form_pg_type typform;
	Oid			oldNspOid;
	Oid			arrayOid;
	bool		isCompositeType;

	rel = heap_open(TypeRelationId, RowExclusiveLock);

	tup = SearchSysCacheCopy1(TYPEOID, ObjectIdGetDatum(typeOid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", typeOid);
	typform = (Form_pg_type) GETSTRUCT(tup);

	oldNspOid = typform->typnamespace;
	arrayOid = typform->typarray;


	CheckSetNamespace(oldNspOid, nspOid, TypeRelationId, typeOid);


	if (SearchSysCacheExists2(TYPENAMENSP,
							  CStringGetDatum(NameStr(typform->typname)),
							  ObjectIdGetDatum(nspOid)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("type \"%s\" already exists in schema \"%s\"",
						NameStr(typform->typname),
						get_namespace_name(nspOid))));


	isCompositeType =
		(typform->typtype == TYPTYPE_COMPOSITE &&
		 get_rel_relkind(typform->typrelid) == RELKIND_COMPOSITE_TYPE);


	if (typform->typtype == TYPTYPE_COMPOSITE && !isCompositeType &&
		errorOnTableType)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("%s is a table's row type",
						format_type_be(typeOid)),
				 errhint("Use ALTER TABLE instead.")));


	typform->typnamespace = nspOid;

	simple_heap_update(rel, &tup->t_self, tup);
	CatalogUpdateIndexes(rel, tup);


	if (isCompositeType)
	{
		Relation	classRel;

		classRel = heap_open(RelationRelationId, RowExclusiveLock);

		AlterRelationNamespaceInternal(classRel, typform->typrelid,
									   oldNspOid, nspOid,
									   false);

		heap_close(classRel, RowExclusiveLock);


		AlterConstraintNamespaces(typform->typrelid, oldNspOid,
								  nspOid, false);
	}
	else
	{

		if (typform->typtype == TYPTYPE_DOMAIN)
			AlterConstraintNamespaces(typeOid, oldNspOid, nspOid, true);
	}


	if ((isCompositeType || typform->typtype != TYPTYPE_COMPOSITE) &&
		!isImplicitArray)
		if (changeDependencyFor(TypeRelationId, typeOid,
								NamespaceRelationId, oldNspOid, nspOid) != 1)
			elog(ERROR, "failed to change schema dependency for type %s",
				 format_type_be(typeOid));

	heap_freetuple(tup);

	heap_close(rel, RowExclusiveLock);


	if (OidIsValid(arrayOid))
		AlterTypeNamespaceInternal(arrayOid, nspOid, true, true);

	return oldNspOid;
}
