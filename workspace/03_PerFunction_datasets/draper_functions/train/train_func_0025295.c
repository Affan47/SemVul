filter_write(void *data, const char *buf, size_t size, size_t *pret)
{
    struct filter_stream *fs = data;
    size_t ret = 0;
    size_t wrs;
    int rc = 0;

    if (size < fs->min_level
	|| (fs->inlevel && fs->inlevel < fs->min_level)) {
	size_t rest = fs->min_level - fs->inlevel;
	if (rest > size)
	    rest = size;
	memcpy(fs->inbuf + fs->inlevel, buf, rest);
	fs->inlevel += rest;
	if (fs->inlevel < fs->min_level) {
	    *pret = rest;
	    return 0;
	}
	buf += rest;
	size -= rest;

	rc = filter_write0(fs, fs->inbuf, fs->inlevel, &wrs);
	if (rc)
	    return rc;
	if (wrs != fs->inlevel) {

	    return 1;
	}
	fs->inlevel = 0;
	ret = rest;
    }
    if (size)
	rc = filter_write0(fs, buf, size, &wrs);
    else {
	rc = 0;
	wrs = 0;
    }
    if (rc == 0) {
	ret += wrs;
	*pret = ret;
    }
    return rc;
}
