ncx_get_short_uchar(const void *xp, uchar *ip)
{
	ix_short xx;
	get_ix_short(xp, &xx);
	*ip = xx;
	if(xx > UCHAR_MAX || xx < 0)
		return NC_ERANGE;
	return ENOERR;
}
