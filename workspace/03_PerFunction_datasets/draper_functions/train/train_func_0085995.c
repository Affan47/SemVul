enum_cmp(PG_FUNCTION_ARGS)
{
	Oid			a = PG_GETARG_OID(0);
	Oid			b = PG_GETARG_OID(1);

	if (a == b)
		PG_RETURN_INT32(0);
	else if (enum_cmp_internal(a, b, fcinfo) > 0)
		PG_RETURN_INT32(1);
	else
		PG_RETURN_INT32(-1);
}
