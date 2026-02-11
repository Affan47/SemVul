i2b(int i)
{
    Bigint *b;

    b = Balloc(1);
    if (b == NULL)
        return NULL;
    b->x[0] = i;
    b->wds = 1;
    return b;
}
