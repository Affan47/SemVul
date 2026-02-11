mu_stpcpy (char **pbuf, size_t *psize, const char *src)
{
    size_t slen = strlen (src);
    if (pbuf == NULL || *pbuf == NULL)
	return slen;
    else {
	char *buf = *pbuf;
	size_t size = *psize;
	if (size > slen)
	    size = slen;
	memcpy (buf, src, size);
	*psize -= size;
	*pbuf += size;
	if (*psize)
	    **pbuf = 0;
	else
	    (*pbuf)[-1] = 0;
	return size;
    }
}
