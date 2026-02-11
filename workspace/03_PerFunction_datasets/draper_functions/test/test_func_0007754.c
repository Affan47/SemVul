reset(snefru_ty *s)
{
    int             i;

    for (i = 0; i < 64; ++i)
        s->c[i] = 0;
    for (i = 0; i < 8; ++i)
        s->len[i] = 0;
    s->n = 32;
}
