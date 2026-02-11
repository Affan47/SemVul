utf8_mbstr_to_wc(const char *str, unsigned **wptr, size_t *plen)
{
    ssize_t sc = strlen(str);
    size_t len, i;
    unsigned *w = calloc(sizeof(w[0]), sc + 1);

    if (!w)
	return -1;
    for (i = 0, len = strlen(str); len; i++) {
	int rc = utf8_mbtowc(w + i, str, len);
	if (rc <= 0) {
	    free(w);
	    return -1;
	}
	str += rc;
	len -= rc;
    }
    *wptr = w;
    if (plen)
	*plen = sc;
    return 0;
}
