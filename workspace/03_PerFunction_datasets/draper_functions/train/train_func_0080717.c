ConversionIsVisible(Oid conid)
{
	HeapTuple	contup;
	Form_pg_conversion conform;
	Oid			connamespace;
	bool		visible;

	contup = SearchSysCache1(CONVOID, ObjectIdGetDatum(conid));
	if (!HeapTupleIsValid(contup))
		elog(ERROR, "cache lookup failed for conversion %u", conid);
	conform = (Form_pg_conversion) GETSTRUCT(contup);

	recomputeNamespacePath();


	connamespace = conform->connamespace;
	if (connamespace != PG_CATALOG_NAMESPACE &&
		!list_member_oid(activeSearchPath, connamespace))
		visible = false;
	else
	{


		char	   *conname = NameStr(conform->conname);

		visible = (ConversionGetConid(conname) == conid);
	}

	ReleaseSysCache(contup);

	return visible;
}
