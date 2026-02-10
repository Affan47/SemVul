qexp_func_defined (Bonobo_ServerInfo * si, QueryExpr * e, QueryContext * qctx)
{
	QueryExprConst retval, v1;

	v1 = qexp_evaluate (si, e->u.function_value.arguments->data, qctx);

	retval.value_known = TRUE;

	retval.type = CONST_BOOLEAN;

	retval.u.v_boolean = v1.value_known ? TRUE : FALSE;

	retval.needs_free = FALSE;

	qexp_constant_unuse (v1);

	return retval;
}
