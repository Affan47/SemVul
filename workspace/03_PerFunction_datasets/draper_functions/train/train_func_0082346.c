gin_extract_jsonb(PG_FUNCTION_ARGS)
{
	Jsonb	   *jb = (Jsonb *) PG_GETARG_JSONB(0);
	int32	   *nentries = (int32 *) PG_GETARG_POINTER(1);
	int			total = 2 * JB_ROOT_COUNT(jb);
	JsonbIterator *it;
	JsonbValue	v;
	int			i = 0,
				r;
	Datum	   *entries;


	if (total == 0)
	{
		*nentries = 0;
		PG_RETURN_POINTER(NULL);
	}


	entries = (Datum *) palloc(sizeof(Datum) * total);

	it = JsonbIteratorInit(&jb->root);

	while ((r = JsonbIteratorNext(&it, &v, false)) != WJB_DONE)
	{

		if (i >= total)
		{
			total *= 2;
			entries = (Datum *) repalloc(entries, sizeof(Datum) * total);
		}

		switch (r)
		{
			case WJB_KEY:
				entries[i++] = make_scalar_key(&v, true);
				break;
			case WJB_ELEM:

				entries[i++] = make_scalar_key(&v, (v.type == jbvString));
				break;
			case WJB_VALUE:
				entries[i++] = make_scalar_key(&v, false);
				break;
			default:

				break;
		}
	}

	*nentries = i;

	PG_RETURN_POINTER(entries);
}
