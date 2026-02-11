utoa_internal_dup(wchar_t const *s, int charset, int *lenp, int careful)
{
    char *outbuf;
    int outpos, outlen, len, ret, err;
    charset_state state = CHARSET_INIT_STATE;

    if (!s) {
	return dupstr("");
    }

    len = ustrlen(s);

    outlen = len + 10;
    outbuf = snewn(outlen, char);

    outpos = 0;
    outbuf[outpos] = '\0';

    while (len > 0) {
	err = 0;
	ret = charset_from_unicode(&s, &len,
				   outbuf + outpos, outlen - outpos - 1,
				   charset, &state, (careful ? &err : NULL));
	if (err) {
	    sfree(outbuf);
	    return NULL;
	}
	if (!ret) {
	    outlen = outlen * 3 / 2;
	    outbuf = sresize(outbuf, outlen, char);
	}
	outpos += ret;
	outbuf[outpos] = '\0';
    }


    outlen = outpos + 32;
    outbuf = sresize(outbuf, outlen, char);
    ret = charset_from_unicode(NULL, 0,
			       outbuf + outpos, outlen - outpos + 1,
			       charset, &state, NULL);
    outpos += ret;
    outbuf[outpos] = '\0';
    if (lenp)
	*lenp = outpos;
    return outbuf;
}
