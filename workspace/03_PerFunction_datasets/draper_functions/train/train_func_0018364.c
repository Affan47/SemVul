record_help(struct helpfile *hf, const char htype, const long h1, const long h2)
{
	unsigned  long	hashval = (unsigned long) (((int) htype) * 97 + h2 * 13 + h1) % HELPHASH;
	struct	hadhelp	*hv;

	for  (hv = hf->hf_hash[hashval];  hv;  hv = hv->had_next)
		if  (hv->had_char == htype && hv->had_value == h1 && hv->had_state == h2)  {
			fprintf(stderr, "Warning: duplicate %ld %c %ld in help file %s\n", h2, htype, h1, hf->hf_name);
			return;
		}

	if  (!(hv = (struct hadhelp *) malloc(sizeof(struct hadhelp))))
		nomem();
	hv->had_next = hf->hf_hash[hashval];
	hf->hf_hash[hashval] = hv;
	hv->had_value = h1;
	hv->had_state = h2;
	hv->had_char = htype;
}
