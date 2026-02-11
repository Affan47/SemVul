hts_readlines(const char *fn, int *_n)
{
	int m = 0, n = 0, dret;
	char **s = 0;
#if KS_BGZF
	BGZF *fp = bgzf_open(fn, "r");
#else
	gzFile fp = gzopen(fn, "r");
#endif
	if ( fp ) {
		kstream_t *ks;
		kstring_t str;
		str.s = 0; str.l = str.m = 0;
		ks = ks_init(fp);
		while (ks_getuntil(ks, KS_SEP_LINE, &str, &dret) >= 0) {
			if (str.l == 0) continue;
			if (m == n) {
				m = m? m<<1 : 16;
				s = (char**)realloc(s, m * sizeof(void*));
			}
			s[n++] = strdup(str.s);
		}
		ks_destroy(ks);
        #if KS_BGZF
            bgzf_close(fp);
        #else
		    gzclose(fp);
        #endif
		s = (char**)realloc(s, n * sizeof(void*));
		free(str.s);
	} else if (*fn == ':') {
		const char *q, *p;
		for (q = p = fn + 1;; ++p)
			if (*p == ',' || *p == 0) {
				if (m == n) {
					m = m? m<<1 : 16;
					s = (char**)realloc(s, m * sizeof(void*));
				}
				s[n] = (char*)calloc(p - q + 1, 1);
				strncpy(s[n++], q, p - q);
				q = p + 1;
				if (*p == 0) break;
			}
	} else return 0;
	s = (char**)realloc(s, n * sizeof(void*));
	*_n = n;
	return s;
}
