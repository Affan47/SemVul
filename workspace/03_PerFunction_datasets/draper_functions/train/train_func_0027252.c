gtsvector_decompress(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	SignTSVector *key = (SignTSVector *) DatumGetPointer(PG_DETOAST_DATUM(entry->key));

	if (key != (SignTSVector *) DatumGetPointer(entry->key))
	{
		GISTENTRY  *retval = (GISTENTRY *) palloc(sizeof(GISTENTRY));

		gistentryinit(*retval, PointerGetDatum(key),
					  entry->rel, entry->page,
					  entry->offset, FALSE);

		PG_RETURN_POINTER(retval);
	}

	PG_RETURN_POINTER(entry);
}
