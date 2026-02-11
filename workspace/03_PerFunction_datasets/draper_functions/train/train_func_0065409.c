l_byteaFindEachSequence(L_BYTEA   *ba,
                        l_uint8   *sequence,
                        l_int32    seqlen,
                        L_DNA    **pda)
{
l_uint8  *data;
size_t    size;

    PROCNAME("l_byteaFindEachSequence");

    if (!pda)
        return ERROR_INT("&da not defined", procName, 1);
    *pda = NULL;
    if (!ba)
        return ERROR_INT("ba not defined", procName, 1);
    if (!sequence)
        return ERROR_INT("sequence not defined", procName, 1);

    data = l_byteaGetData(ba, &size);
    *pda = arrayFindEachSequence(data, size, sequence, seqlen);
    return 0;
}
