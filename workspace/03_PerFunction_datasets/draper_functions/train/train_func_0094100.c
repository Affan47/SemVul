dname_enc(const uint8_t *cstr, int clen, const char *src, int *retlen)
{
	uint8_t *d, *dname;
	int off;

	dname = convert_dname(src);
	if (dname == NULL) {
		*retlen = 0;
		return NULL;
	}

	d = dname;
	while (*d) {
		if (cstr) {
			off = find_offset(cstr, clen, d);
			if (off >= 0) {
				*d++ = NS_CMPRSFLGS | (off >> 8);
				*d = off;
				break;
			}
		}
		d += *d + 1;
	}

	*retlen = d - dname + 1;
	return dname;
}
