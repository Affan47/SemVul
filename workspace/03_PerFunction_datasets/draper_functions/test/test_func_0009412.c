gethost_byname_type(char *name, Link *lp, int type)
{
	Reg	aCache	*cp;

	reinfo.re_na_look++;

	if (type != T_A
#ifdef INET6
		&& type != T_AAAA
#endif
		)
		return NULL;
	if ((cp = find_cache_name(NULL, name,
#ifdef INET6
		(type == T_AAAA) ? FLG_AAAA_VALID :
#endif
		FLG_A_VALID)))
		return (struct hostent *)&(cp->he);
	if (!lp)
		return NULL;
	(void)do_query_name(lp, name, NULL, type);
	return NULL;
}
