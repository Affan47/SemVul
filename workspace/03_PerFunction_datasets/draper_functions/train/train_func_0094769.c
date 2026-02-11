iconv_string(char *to, char *from,
			char *src, char *dst, size_t max)
{
    size_t ilen = strlen(src);
    size_t olen = max-1;
    iconv_t ic;

    ic = iconv_open(to,from);
    if (NULL == ic)
	return 0;

    while (ilen > 0) {
	if (-1 == iconv(ic,&src,&ilen,&dst,&olen)) {

	    if (E2BIG == errno)
		break;
	    if (olen < 4)
		break;
	    sprintf(dst,"\\x%02x",(int)(unsigned char)src[0]);
	    src  += 1;
	    dst  += 4;
	    ilen -= 1;
	    olen -= 4;
	}
    }
    dst[0] = 0;
    iconv_close(ic);
    return max-1 - olen;
}
