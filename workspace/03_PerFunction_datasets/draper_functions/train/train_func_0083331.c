IsPoly_op(GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	if(check_poly(a,1,"IsPoly",FALSE))
		return gel_makenum_bool (1);
	else
		return gel_makenum_bool (0);
}
