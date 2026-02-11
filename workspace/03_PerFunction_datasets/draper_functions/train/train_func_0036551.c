TypeRename(const char *oldTypeName, Oid typeNamespace,
		   const char *newTypeName)
{
	Relation	pg_type_desc;
	HeapTuple	tuple;

	pg_type_desc = heap_open(TypeRelationId, RowExclusiveLock);

	tuple = SearchSysCacheCopy(TYPENAMENSP,
							   CStringGetDatum(oldTypeName),
							   ObjectIdGetDatum(typeNamespace),
							   0, 0);
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" does not exist", oldTypeName)));

	if (SearchSysCacheExists(TYPENAMENSP,
							 CStringGetDatum(newTypeName),
							 ObjectIdGetDatum(typeNamespace),
							 0, 0))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("type \"%s\" already exists", newTypeName)));

	namestrcpy(&(((Form_pg_type) GETSTRUCT(tuple))->typname), newTypeName);

	simple_heap_update(pg_type_desc, &tuple->t_self, tuple);


	CatalogUpdateIndexes(pg_type_desc, tuple);

	heap_freetuple(tuple);
	heap_close(pg_type_desc, RowExclusiveLock);
}
