handle_empty (GnmValue *res, GnmExprEvalFlags flags)
{
	if (res == NULL)
		return (flags & GNM_EXPR_EVAL_PERMIT_EMPTY)
		    ? NULL : value_new_int (0);

	if (VALUE_IS_EMPTY (res)) {
		value_release (res);
		return (flags & GNM_EXPR_EVAL_PERMIT_EMPTY)
		    ? NULL : value_new_int (0);
	}
	return res;
}
