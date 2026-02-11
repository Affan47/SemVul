typeIsOfTypedTable(Oid reltypeId, Oid reloftypeId)
{
	Oid			relid = typeidTypeRelid(reltypeId);
	bool		result = false;

	if (relid)
	{
		HeapTuple	tp;
		Form_pg_class reltup;

		tp = SearchSysCache1(RELOID, ObjectIdGetDatum(relid));
		if (!HeapTupleIsValid(tp))
			elog(ERROR, "cache lookup failed for relation %u", relid);

		reltup = (Form_pg_class) GETSTRUCT(tp);
		if (reltup->reloftype == reloftypeId)
			result = true;

		ReleaseSysCache(tp);
	}

	return result;
}
