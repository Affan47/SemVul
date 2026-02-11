regnamespacein(PG_FUNCTION_ARGS)
{
	char	   *nsp_name_or_oid = PG_GETARG_CSTRING(0);
	Oid			result = InvalidOid;


	if (strcmp(nsp_name_or_oid, "-") == 0)
		PG_RETURN_OID(InvalidOid);


	if (nsp_name_or_oid[0] >= '0' &&
		nsp_name_or_oid[0] <= '9' &&
		strspn(nsp_name_or_oid, "0123456789") == strlen(nsp_name_or_oid))
	{
		result = DatumGetObjectId(DirectFunctionCall1(oidin,
										  CStringGetDatum(nsp_name_or_oid)));
		PG_RETURN_OID(result);
	}


	result = get_namespace_oid(nsp_name_or_oid, false);

	PG_RETURN_OID(result);
}
