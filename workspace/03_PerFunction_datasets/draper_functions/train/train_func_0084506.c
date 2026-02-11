enum_range_bounds(PG_FUNCTION_ARGS)
{
	Oid			lower;
	Oid			upper;
	Oid			enumtypoid;

	if (PG_ARGISNULL(0))
		lower = InvalidOid;
	else
		lower = PG_GETARG_OID(0);
	if (PG_ARGISNULL(1))
		upper = InvalidOid;
	else
		upper = PG_GETARG_OID(1);


	enumtypoid = get_fn_expr_argtype(fcinfo->flinfo, 0);
	if (enumtypoid == InvalidOid)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("could not determine actual enum type")));

	PG_RETURN_ARRAYTYPE_P(enum_range_internal(enumtypoid, lower, upper));
}
