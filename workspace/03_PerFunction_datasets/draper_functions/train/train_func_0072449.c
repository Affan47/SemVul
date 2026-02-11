build_dummy_tuple(CatCache *cache, int nkeys, ScanKey skeys)
{
	HeapTuple	ntp;
	TupleDesc	tupDesc = cache->cc_tupdesc;
	Datum	   *values;
	bool	   *nulls;
	Oid			tupOid = InvalidOid;
	NameData	tempNames[4];
	int			i;

	values = (Datum *) palloc(tupDesc->natts * sizeof(Datum));
	nulls = (bool *) palloc(tupDesc->natts * sizeof(bool));

	memset(values, 0, tupDesc->natts * sizeof(Datum));
	memset(nulls, true, tupDesc->natts * sizeof(bool));

	for (i = 0; i < nkeys; i++)
	{
		int			attindex = cache->cc_key[i];
		Datum		keyval = skeys[i].sk_argument;

		if (attindex > 0)
		{


			if (cache->cc_isname[i])
			{
				Name		newval = &tempNames[i];

				namestrcpy(newval, DatumGetCString(keyval));
				keyval = NameGetDatum(newval);
			}
			values[attindex - 1] = keyval;
			nulls[attindex - 1] = false;
		}
		else
		{
			Assert(attindex == ObjectIdAttributeNumber);
			tupOid = DatumGetObjectId(keyval);
		}
	}

	ntp = heap_form_tuple(tupDesc, values, nulls);
	if (tupOid != InvalidOid)
		HeapTupleSetOid(ntp, tupOid);

	pfree(values);
	pfree(nulls);

	return ntp;
}
