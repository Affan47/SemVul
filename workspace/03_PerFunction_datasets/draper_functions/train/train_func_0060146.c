get_attname(Oid relid, AttrNumber attnum)
{
	HeapTuple	tp;

	tp = SearchSysCache(ATTNUM,
						ObjectIdGetDatum(relid),
						Int16GetDatum(attnum),
						0, 0);
	if (HeapTupleIsValid(tp))
	{
		Form_pg_attribute att_tup = (Form_pg_attribute) GETSTRUCT(tp);
		char	   *result;

		result = pstrdup(NameStr(att_tup->attname));
		ReleaseSysCache(tp);
		return result;
	}
	else
		return NULL;
}
