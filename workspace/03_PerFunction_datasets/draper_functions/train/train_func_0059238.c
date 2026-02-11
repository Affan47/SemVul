compatible_oper(ParseState *pstate, List *op, Oid arg1, Oid arg2,
				bool noError, int location)
{
	Operator	optup;
	Form_pg_operator opform;


	optup = oper(pstate, op, arg1, arg2, noError, location);
	if (optup == (Operator) NULL)
		return (Operator) NULL;


	opform = (Form_pg_operator) GETSTRUCT(optup);
	if (IsBinaryCoercible(arg1, opform->oprleft) &&
		IsBinaryCoercible(arg2, opform->oprright))
		return optup;


	ReleaseSysCache(optup);

	if (!noError)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("operator requires run-time type coercion: %s",
						op_signature_string(op, 'b', arg1, arg2)),
				 parser_errposition(pstate, location)));

	return (Operator) NULL;
}
