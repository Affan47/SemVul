qexp_evaluate (Bonobo_ServerInfo * si, QueryExpr * e, QueryContext * qctx)
{
	QueryExprConst retval;

	if (e->have_cached_value) {
		retval = e->cached_value;
	} else {
		switch (e->type) {
		case EXPR_FUNCTION:
			retval = qexp_evaluate_function (si, e, qctx);
			break;
		case EXPR_VARIABLE:
			retval = qexp_evaluate_variable (si, e, qctx);
			break;
		case EXPR_ID:
			retval = qexp_evaluate_id (si, e, qctx);
			break;
		case EXPR_BINOP:
			retval = qexp_evaluate_binop (si, e, qctx);
			break;
		case EXPR_UNOP:
			retval = qexp_evaluate_unop (si, e, qctx);
			break;
		case EXPR_CONSTANT:
			retval = qexp_evaluate_constant (si, e, qctx);
			break;
		}
	}

	if (!e->has_fields) {
		e->cached_value = retval;
		e->have_cached_value = TRUE;
		retval.needs_free = FALSE;
	}

	return retval;
}
