generateHuffBases (int index, int * n, INT64 ** huffBases)
{
    int err = OK,
        i = 1;
    INT64 base = 1;


    *huffBases = (INT64 *) malloc(10 * sizeof(INT64));
    if (*huffBases)
    {
        (*huffBases)[0] = 0;
        while ( BitAmounts[index][i] != -1)
        {
            (*huffBases)[i] = base;
            base += 1 << (BitAmounts[index][i]-1);
            i++;
        }
        *n = i;
    } else {
        err = OUT_OF_MEMORY;
    }
    return err;
}
