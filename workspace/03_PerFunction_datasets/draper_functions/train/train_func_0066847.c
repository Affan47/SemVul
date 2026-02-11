gnm_expr_get_range (GnmExpr const *expr)
{
	g_return_val_if_fail (expr != NULL, NULL);

	switch (GNM_EXPR_GET_OPER (expr)) {
	case GNM_EXPR_OP_CELLREF:
		return value_new_cellrange_unsafe (
			&expr->cellref.ref, &expr->cellref.ref);

	case GNM_EXPR_OP_CONSTANT:
		if (expr->constant.value->type == VALUE_CELLRANGE)
			return value_dup (expr->constant.value);
		return NULL;

	case GNM_EXPR_OP_NAME:
		if (!expr_name_is_active (expr->name.name))
			return NULL;
		return gnm_expr_top_get_range (expr->name.name->texpr);

	case GNM_EXPR_OP_PAREN:
		return gnm_expr_get_range (expr->unary.value);

	default:
		return NULL;
	}
}
