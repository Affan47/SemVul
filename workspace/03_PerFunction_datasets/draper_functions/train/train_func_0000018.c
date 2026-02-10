der_put_general_string (unsigned char *p, size_t len,
			const general_string *str, size_t *size)
{
    size_t slen = strlen(*str);

    if (len < slen)
	return ASN1_OVERFLOW;
    p -= slen;
    len -= slen;
    memcpy (p+1, *str, slen);
    *size = slen;
    return 0;
}
