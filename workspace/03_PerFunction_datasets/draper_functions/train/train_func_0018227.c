bi_export(BI_CTX *ctx, bigint *x, uint8_t *data, int size)
{
    int i, j, k = size-1;

    check(x);
    memset(data, 0, size);

    for (i = 0; i < x->size; i++)
    {
        for (j = 0; j < COMP_BYTE_SIZE; j++)
        {
            comp mask = 0xff << (j*8);
            int num = (x->comps[i] & mask) >> (j*8);
            data[k--] = num;

            if (k < 0)
            {
                break;
            }
        }
    }

    bi_free(ctx, x);
}
