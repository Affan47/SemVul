convert_function_name(text *functionname)
{
	char	   *funcname = text_to_cstring(functionname);
	Oid			oid;

	oid = DatumGetObjectId(DirectFunctionCall1(regprocedurein,
											   CStringGetDatum(funcname)));

	if (!OidIsValid(oid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("function \"%s\" does not exist", funcname)));

	return oid;
}
