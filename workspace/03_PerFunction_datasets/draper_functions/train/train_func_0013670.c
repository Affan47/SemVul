simple_mult_addr_string(struct mail_address *addr, char *buf, size_t buflen, char *sep)
{
    ADDRESS *a;
    char    *dest = buf;
    size_t   seplen = 0;

    if(sep)
      seplen = strlen(sep);

    *dest = '\0';
    for(a = addr; a; a = a->next){
	if(dest > buf && seplen > 0 && buflen-1-(dest-buf) >= seplen){
	    strncpy(dest, sep, seplen);
	    dest += seplen;
	    *dest = '\0';
	}

	simple_addr_string(a, dest, buflen-(dest-buf));
	dest += strlen(dest);
    }

    buf[buflen-1] = '\0';

    return(buf);
}
