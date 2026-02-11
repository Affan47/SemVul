bcatcstr (bstring b, const char * s) {
char * d;
int i, l;

	if (b == NULL || b->data == NULL || b->slen < 0 || b->mlen < b->slen
	 || b->mlen <= 0 || s == NULL) return BSTR_ERR;


	l = b->mlen - b->slen;
	d = (char *) &b->data[b->slen];
	for (i=0; i < l; i++) {
		if ((*d++ = *s++) == '\0') {
			b->slen += i;
			return BSTR_OK;
		}
	}
	b->slen += i;


	return bcatblk (b, (const void *) s, (int) strlen (s));
}
