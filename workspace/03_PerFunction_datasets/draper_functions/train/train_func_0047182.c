bbufferCreate(l_uint8  *indata,
              l_int32   nalloc)
{
BBUFFER  *bb;

    PROCNAME("bbufferCreate");

    if (nalloc <= 0)
        nalloc = INITIAL_BUFFER_ARRAYSIZE;

    if ((bb = (BBUFFER *)CALLOC(1, sizeof(BBUFFER))) == NULL)
        return (BBUFFER *)ERROR_PTR("bb not made", procName, NULL);
    if ((bb->array = (l_uint8 *)CALLOC(nalloc, sizeof(l_uint8))) == NULL)
        return (BBUFFER *)ERROR_PTR("byte array not made", procName, NULL);
    bb->nalloc = nalloc;
    bb->nwritten = 0;

    if (indata) {
        memcpy((l_uint8 *)bb->array, indata, nalloc);
        bb->n = nalloc;
    }
    else
        bb->n = 0;

    return bb;
}
