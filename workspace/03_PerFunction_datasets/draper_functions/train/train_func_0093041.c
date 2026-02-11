gist_poly_compress(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	GISTENTRY  *retval;

	if (entry->leafkey)
	{
		POLYGON    *in = DatumGetPolygonP(entry->key);
		BOX		   *r;

		r = (BOX *) palloc(sizeof(BOX));
		memcpy((void *) r, (void *) &(in->boundbox), sizeof(BOX));

		retval = (GISTENTRY *) palloc(sizeof(GISTENTRY));
		gistentryinit(*retval, PointerGetDatum(r),
					  entry->rel, entry->page,
					  entry->offset, FALSE);
	}
	else
		retval = entry;
	PG_RETURN_POINTER(retval);
}
