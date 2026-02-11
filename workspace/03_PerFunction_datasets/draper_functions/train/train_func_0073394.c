build_range_ctor (GnmExpr *l, GnmExpr *r, GnmExpr *validate)
{
	if (!l || !r) return NULL;

	if (validate != NULL) {
		if (GNM_EXPR_GET_OPER (validate) != GNM_EXPR_OP_CELLREF ||
		    validate->cellref.ref.sheet != NULL) {
			report_err (state, g_error_new (1, PERR_UNEXPECTED_TOKEN,
				_("Constructed ranges use simple references")),
				state->ptr, 0);
			return NULL;
		    }
	}

	unregister_allocation (r);
	unregister_allocation (l);
	return register_expr_allocation (gnm_expr_new_range_ctor (l, r));
}
