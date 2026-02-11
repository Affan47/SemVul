rv_alloc(int i)
{
    int j, k, *r;

    j = sizeof(ULong);
    for(k = 0;
        sizeof(Bigint) - sizeof(ULong) - sizeof(int) + j <= (unsigned)i;
        j <<= 1)
        k++;
    r = (int*)Balloc(k);
    if (r == NULL)
        return NULL;
    *r = k;
    return (char *)(r+1);
}
