pg_get_userbyid(PG_FUNCTION_ARGS)
{
	Oid			roleid = PG_GETARG_OID(0);
	Name		result;
	HeapTuple	roletup;
	Form_pg_authid role_rec;


	result = (Name) palloc(NAMEDATALEN);
	memset(NameStr(*result), 0, NAMEDATALEN);


	roletup = SearchSysCache(AUTHOID,
							 ObjectIdGetDatum(roleid),
							 0, 0, 0);
	if (HeapTupleIsValid(roletup))
	{
		role_rec = (Form_pg_authid) GETSTRUCT(roletup);
		StrNCpy(NameStr(*result), NameStr(role_rec->rolname), NAMEDATALEN);
		ReleaseSysCache(roletup);
	}
	else
		sprintf(NameStr(*result), "unknown (OID=%u)", roleid);

	PG_RETURN_NAME(result);
}
