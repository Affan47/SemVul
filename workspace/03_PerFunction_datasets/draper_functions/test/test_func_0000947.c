gnm_expr_top_as_string (GnmExprTop const *texpr,
			GnmParsePos const *pp,
			GnmConventions const *convs)
{
	g_return_val_if_fail (IS_GNM_EXPR_TOP (texpr), NULL);

	return gnm_expr_as_string (texpr->expr, pp, convs);
}
