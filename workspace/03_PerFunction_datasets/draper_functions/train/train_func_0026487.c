makeArrayTypeName(const char *typeName, Oid typeNamespace)
{
	char	   *arr = (char *) palloc(NAMEDATALEN);
	int			namelen = strlen(typeName);
	Relation	pg_type_desc;
	int			i;


	pg_type_desc = heap_open(TypeRelationId, AccessShareLock);

	for (i = 1; i < NAMEDATALEN - 1; i++)
	{
		arr[i - 1] = '_';
		if (i + namelen < NAMEDATALEN)
			strcpy(arr + i, typeName);
		else
		{
			memcpy(arr + i, typeName, NAMEDATALEN - i);
			truncate_identifier(arr, NAMEDATALEN, false);
		}
		if (!SearchSysCacheExists(TYPENAMENSP,
								  CStringGetDatum(arr),
								  ObjectIdGetDatum(typeNamespace),
								  0, 0))
			break;
	}

	heap_close(pg_type_desc, AccessShareLock);

	if (i >= NAMEDATALEN - 1)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("could not form array type name for type \"%s\"",
						typeName)));

	return arr;
}
