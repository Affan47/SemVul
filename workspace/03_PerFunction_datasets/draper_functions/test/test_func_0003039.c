cmpstringop (GelCtx *ctx, GelETree *n, GelETree *l, GelETree *r)
{
	int ret;
	ret = cmpstring (l, r);

	freetree_full (n, TRUE, FALSE);

	if (ret > 0)
		gel_makenum_ui_from (n, 1);
	else if (ret <0 )
		gel_makenum_si_from (n, -1);
	else
		gel_makenum_ui_from (n, 0);
	return TRUE;
}
