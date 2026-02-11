getDatumCopy(BuildAccumulator *accum, Datum value)
{
	Form_pg_attribute *att = accum->ginstate->tupdesc->attrs;
	Datum		res;

	if (att[0]->attbyval)
		res = value;
	else
	{
		Size		realSize;
		char	   *s;

		realSize = datumGetSize(value, false, att[0]->attlen);

		s = (char *) palloc(realSize);
		memcpy(s, DatumGetPointer(value), realSize);
		res = PointerGetDatum(s);

		accum->allocatedMemory += realSize;
	}
	return res;
}
