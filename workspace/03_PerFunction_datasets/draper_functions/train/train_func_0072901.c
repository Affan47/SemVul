rfc1522_8bit(void *src, int slen)
{
    char *ret = (char *) fs_get ((size_t) (3*slen + 2));
    char *d = ret;
    unsigned char c;
    unsigned char *s = (unsigned char *) src;

    while (slen--) {
	if (((c = *s++) == '\015') && (*s == '\012') && slen) {
	    *d++ = '\015';
	    *d++ = *s++;
	    slen--;
	}
	else if(c == SPACE){
	    *d++ = '_';
	}
	else if(RFC1522_ENC_CHAR(c)){
	    *d++ = '=';
	    C2XPAIR(c, d);
	}
	else
	  *d++ = (char) c;
    }

    *d = '\0';
    return(ret);
}
