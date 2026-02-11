ncx_put_short_int(void *xp, const int *ip)
{
#if SIZEOF_IX_SHORT == SIZEOF_INT && X_SHORT_MAX == INT_MAX
	put_ix_short(xp, (const ix_short *)ip);
	return ENOERR;
#else
	ix_short xx = (ix_short)*ip;
	put_ix_short(xp, &xx);
# if X_SHORT_MAX < INT_MAX
	if(*ip > X_SHORT_MAX || *ip < X_SHORT_MIN)
		return NC_ERANGE;
# endif
	return ENOERR;
#endif
}
