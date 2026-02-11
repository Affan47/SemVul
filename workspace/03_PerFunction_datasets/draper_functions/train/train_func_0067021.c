ncx_get_double_float(const void *xp, float *ip)
{
	double xx;
	get_ix_double(xp, &xx);
	if(xx > FLT_MAX || xx < (-FLT_MAX))
	{
		*ip = FLT_MAX;
		return NC_ERANGE;
	}
	if(xx < (-FLT_MAX))
	{
		*ip = (-FLT_MAX);
		return NC_ERANGE;
	}
	*ip = (float) xx;
	return ENOERR;
}
