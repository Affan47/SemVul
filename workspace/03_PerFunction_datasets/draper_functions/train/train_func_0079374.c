Balloc(int k)
{
    int x;
    Bigint *rv;
    unsigned int len;

    if (k <= Kmax && (rv = freelist[k]))
        freelist[k] = rv->next;
    else {
        x = 1 << k;
        len = (sizeof(Bigint) + (x-1)*sizeof(ULong) + sizeof(double) - 1)
            /sizeof(double);
        if (k <= Kmax && pmem_next - private_mem + len <= PRIVATE_mem) {
            rv = (Bigint*)pmem_next;
            pmem_next += len;
        }
        else {
            rv = (Bigint*)MALLOC(len*sizeof(double));
            if (rv == NULL)
                return NULL;
        }
        rv->k = k;
        rv->maxwds = x;
    }
    rv->sign = rv->wds = 0;
    return rv;
}
