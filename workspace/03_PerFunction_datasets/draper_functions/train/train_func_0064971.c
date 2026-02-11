AlterSchemaOwner(const char *name, Oid newOwnerId)
{
	HeapTuple	tup;
	Relation	rel;

	rel = heap_open(NamespaceRelationId, RowExclusiveLock);

	tup = SearchSysCache(NAMESPACENAME,
						 CStringGetDatum(name),
						 0, 0, 0);
	if (!HeapTupleIsValid(tup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_SCHEMA),
				 errmsg("schema \"%s\" does not exist", name)));

	AlterSchemaOwner_internal(tup, rel, newOwnerId);

	ReleaseSysCache(tup);

	heap_close(rel, RowExclusiveLock);
}
