der_heim_bit_string_cmp(const heim_bit_string *p,
			const heim_bit_string *q)
{
    int r1, r2;
    size_t i;
    if (p->length != q->length)
	return (int)(p->length - q->length);
    i = memcmp(p->data, q->data, p->length / 8);
    if (i)
	return (int)i;
    if ((p->length % 8) == 0)
	return 0;
    i = (p->length / 8);
    r1 = ((unsigned char *)p->data)[i];
    r2 = ((unsigned char *)q->data)[i];
    i = 8 - (p->length % 8);
    r1 = r1 >> i;
    r2 = r2 >> i;
    return r1 - r2;
}
