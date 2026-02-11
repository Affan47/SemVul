regprocedureout(PG_FUNCTION_ARGS)
{
	RegProcedure proid = PG_GETARG_OID(0);
	char	   *result;

	if (proid == InvalidOid)
		result = pstrdup("-");
	else
		result = format_procedure(proid);

	PG_RETURN_CSTRING(result);
}
