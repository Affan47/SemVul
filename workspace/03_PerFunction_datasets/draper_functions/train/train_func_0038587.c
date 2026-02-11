addstrbuf(len)
ALLOC_T len;
{
	u_char *cp;
	ALLOC_T size;

	len += maxstr;
	size = (strbufsize) ? strbufsize : DICTBUFUNIT;
	while (size < len) size *= 2;
	if (size <= strbufsize) return(0);
	if (!(cp = Xrealloc(strbuf, size))) return(-1);
	strbuf = cp;
	strbufsize = size;

	return(0);
}
