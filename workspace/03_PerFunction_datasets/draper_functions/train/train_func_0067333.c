bcf_load_pos(const char *fn, bcf_hdr_t *_h)
{
	void *str2id;
	gzFile fp;
	kstream_t *ks;
	int ret, dret, lineno = 1;
	kstring_t *str;
	khash_t(set64) *hash = 0;

	hash = kh_init(set64);
	str2id = bcf_build_refhash(_h);
	str = calloc(1, sizeof(kstring_t));
	fp = strcmp(fn, "-")? gzopen(fn, "r") : gzdopen(fileno(stdin), "r");
	ks = ks_init(fp);
	while (ks_getuntil(ks, 0, str, &dret) >= 0) {
		int tid = bcf_str2id(str2id, str->s);
		if (tid >= 0 && dret != '\n') {
			if (ks_getuntil(ks, 0, str, &dret) >= 0) {
				uint64_t x = (uint64_t)tid<<32 | (atoi(str->s) - 1);
				kh_put(set64, hash, x, &ret);
			} else break;
		} else fprintf(stderr, "[%s] %s is not a reference name (line %d).\n", __func__, str->s, lineno);
		if (dret != '\n') while ((dret = ks_getc(ks)) > 0 && dret != '\n');
		if (dret < 0) break;
		++lineno;
	}
	bcf_str2id_destroy(str2id);
	ks_destroy(ks);
	gzclose(fp);
	free(str->s); free(str);
	return hash;
}
