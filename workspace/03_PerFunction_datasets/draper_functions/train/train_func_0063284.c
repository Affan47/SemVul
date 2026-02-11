der_get_general_string (const unsigned char *p, size_t len,
			heim_general_string *str, size_t *size)
{
    const unsigned char *p1;
    char *s;

    p1 = memchr(p, 0, len);
    if (p1 != NULL) {


	while ((size_t)(p1 - p) < len && *p1 == '\0')
	    p1++;
	if ((size_t)(p1 - p) != len) {
	    *str = NULL;
	    return ASN1_BAD_CHARACTER;
	}
    }
    if (len > len + 1) {
	*str = NULL;
	return ASN1_BAD_LENGTH;
    }

    *str = s = malloc (len + 1);
    if (s == NULL)
	return ENOMEM;
    memcpy (s, p, len);
    s[len] = '\0';

    if(size) *size = len;
    return 0;
}
