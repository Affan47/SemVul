from_backend(void *frontend, int is_stderr, const char *data, int datalen)
{
    unsigned char *p = (unsigned char *) data;
    unsigned len = (unsigned) datalen;


    if (is_stderr) {
	if (len > 0)
	    if (fwrite(data, 1, len, stderr) < len)
		;
	return 0;
    }


    if (!outptr)
	return 0;

    if ((outlen > 0) && (len > 0)) {
	unsigned used = outlen;
	if (used > len)
	    used = len;
	memcpy(outptr, p, used);
	outptr += used;
	outlen -= used;
	p += used;
	len -= used;
    }

    if (len > 0) {
	if (pendsize < pendlen + len) {
	    pendsize = pendlen + len + 4096*4;
	    pending = sresize(pending, pendsize, unsigned char);
	}
	memcpy(pending + pendlen, p, len);
	pendlen += len;
    }

    return 0;
}
