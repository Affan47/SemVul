der_put_tag(unsigned char *p, size_t len, Der_class class, Der_type type,
	    int tag, size_t *size)
{
	if (len < 1U)
		return (ASN1_OVERFLOW);
	*p = (class << 6) | (type << 5) | tag;
	*size = 1;
	return (0);
}
