prfind(P *p, unsigned char *s, int len)
{
	P *q = pdup(p, USTR "prfind");

	if (frfind(q, s, len)) {
		rgetto(p, q);
		prm(q);
		return p;
	} else {
		prm(q);
		return NULL;
	}
}
