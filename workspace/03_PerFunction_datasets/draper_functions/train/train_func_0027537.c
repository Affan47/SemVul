get_extension_name(Oid ext_oid)
{
	char	   *result;
	Relation	rel;
	SysScanDesc scandesc;
	HeapTuple	tuple;
	ScanKeyData entry[1];

	rel = heap_open(ExtensionRelationId, AccessShareLock);

	ScanKeyInit(&entry[0],
				ObjectIdAttributeNumber,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(ext_oid));

	scandesc = systable_beginscan(rel, ExtensionOidIndexId, true,
								  NULL, 1, entry);

	tuple = systable_getnext(scandesc);


	if (HeapTupleIsValid(tuple))
		result = pstrdup(NameStr(((Form_pg_extension) GETSTRUCT(tuple))->extname));
	else
		result = NULL;

	systable_endscan(scandesc);

	heap_close(rel, AccessShareLock);

	return result;
}
