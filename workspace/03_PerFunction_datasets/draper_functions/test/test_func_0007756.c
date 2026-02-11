ne_path_unescape(const char *uri)
{
    const char *pnt;
    char *ret, *retpos, buf[5] = { "0x00\0" };
    retpos = ret = ne_malloc(strlen(uri) + 1);
    for (pnt = uri; *pnt != '\0'; pnt++) {
	if (*pnt == '%') {
	    if (!isxdigit((unsigned char) pnt[1]) ||
		!isxdigit((unsigned char) pnt[2])) {

                ne_free(ret);
		return NULL;
	    }
	    buf[2] = *++pnt; buf[3] = *++pnt;
	    *retpos++ = (char)strtol(buf, NULL, 16);
	} else {
	    *retpos++ = *pnt;
	}
    }
    *retpos = '\0';
    return ret;
}
