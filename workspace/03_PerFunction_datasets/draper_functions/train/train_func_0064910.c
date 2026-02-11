xdl_find_func(xdfile_t *xf, long i, char *buf, long sz, long *ll) {


	const char *rec;
	long len;

	*ll = 0;
	while (i-- > 0) {
		len = xdl_get_rec(xf, i, &rec);
		if (len > 0 &&
		    (isalpha((unsigned char)*rec) ||
		     *rec == '_' ||
		     *rec == '$')) {
			if (len > sz)
				len = sz;
			while (0 < len && isspace((unsigned char)rec[len - 1]))
				len--;
			memcpy(buf, rec, len);
			*ll = len;
			return;
		}
	}
}
