gnm_expr_get_boundingbox (GnmExpr const *expr, Sheet const *sheet,
			  GnmRange *bound)
{
	g_return_if_fail (expr != NULL);

	switch (GNM_EXPR_GET_OPER (expr)) {
	case GNM_EXPR_OP_RANGE_CTOR:
	case GNM_EXPR_OP_INTERSECT:
	case GNM_EXPR_OP_ANY_BINARY:
		gnm_expr_get_boundingbox (expr->binary.value_a, sheet, bound);
		gnm_expr_get_boundingbox (expr->binary.value_b, sheet, bound);
		break;

	case GNM_EXPR_OP_ANY_UNARY:
		gnm_expr_get_boundingbox (expr->unary.value, sheet, bound);
		break;

	case GNM_EXPR_OP_FUNCALL: {
		int i;
		for (i = 0; i < expr->func.argc; i++)
			gnm_expr_get_boundingbox (expr->func.argv[i], sheet, bound);
		break;
	}
	case GNM_EXPR_OP_SET: {
		int i;
		for (i = 0; i < expr->set.argc; i++)
			gnm_expr_get_boundingbox (expr->set.argv[i], sheet, bound);
		break;
	}

	case GNM_EXPR_OP_NAME:


		break;

	case GNM_EXPR_OP_CELLREF:
		cellref_boundingbox (&expr->cellref.ref, sheet, bound);
		break;

	case GNM_EXPR_OP_CONSTANT: {
		GnmValue const *v = expr->constant.value;

		if (v->type == VALUE_CELLRANGE) {
			cellref_boundingbox (&v->v_range.cell.a, sheet, bound);
			cellref_boundingbox (&v->v_range.cell.b, sheet, bound);
		}
		break;
	}

	case GNM_EXPR_OP_ARRAY_CORNER:
		gnm_expr_get_boundingbox (expr->array_corner.expr, sheet, bound);
		break;

	case GNM_EXPR_OP_ARRAY_ELEM:

		break;
	}
}
