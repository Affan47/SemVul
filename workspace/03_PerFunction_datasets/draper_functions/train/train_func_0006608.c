der_put_oid (unsigned char *p, size_t len,
	     const oid *data, size_t *size)
{
    unsigned char *base = p;
    int n;

    for (n = data->length - 1; n >= 2; --n) {
	unsigned u = data->components[n];

	if (len < 1)
	    return ASN1_OVERFLOW;
	*p-- = u % 128;
	u /= 128;
	--len;
	while (u > 0) {
	    if (len < 1)
		return ASN1_OVERFLOW;
	    *p-- = 128 + u % 128;
	    u /= 128;
	    --len;
	}
    }
    if (len < 1)
	return ASN1_OVERFLOW;
    *p-- = 40 * data->components[0] + data->components[1];
    *size = base - p;
    return 0;
}
