fmt_priv(struct spdet *up, const int fwidth)
{
	ULONG	priv = up? up->spu_flgs: Spuhdr.sph_flgs;

	if  ((priv & ALLPRIVS) == ALLPRIVS)
		return  (fmt_t) strlen(strcpy(bigbuff, allname));
	else  {
		char	*nxt = bigbuff;
		unsigned  pn, totl = 0, lng;
		for  (pn = 0;  pn < NUM_PRIVS;  pn++)
			if  (priv & privbits[pn])  {
				lng = strlen(strcpy(nxt, privnames[pn]));
				nxt += lng;
				*nxt++ = ' ';
				totl += lng + 1;
			}
		if  (totl == 0)
			return  0;
		*--nxt = '\0';
		return  totl - 1;
	}
}
