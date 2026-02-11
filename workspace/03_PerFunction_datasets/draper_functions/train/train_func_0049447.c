snefru_hash(fingerprint_ty *p, unsigned char *h)
{
    snefru_ty	    *s;
    int		    len[8];
    size_t          i;

    s = (snefru_ty *)p;
    for (i = 0; i < 8; ++i)
	len[i] = s->len[i];
    while (s->n != 32)
	fingerprint_add(p, 0);
    while (s->n != 56)
	fingerprint_add(p, 0);
    for (i = 0; i < 8; ++i)
	fingerprint_add(p, len[7 - i]);
    for (i = 0; i < SNEFRU_HASH_LEN; ++i)
	h[i] = s->c[i];
    reset(s);
    return SNEFRU_HASH_LEN;
}
