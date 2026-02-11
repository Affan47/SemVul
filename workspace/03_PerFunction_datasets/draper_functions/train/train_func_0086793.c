bbufferWrite(BBUFFER  *bb,
             l_uint8  *dest,
             size_t    nbytes,
             size_t   *pnout)
{
l_int32  nleft, nout;

    PROCNAME("bbufferWrite");

    if (!bb)
        return ERROR_INT("bb not defined", procName, 1);
    if (!dest)
        return ERROR_INT("dest not defined", procName, 1);
    if (nbytes <= 0)
        return ERROR_INT("no bytes requested to write", procName, 1);
    if (!pnout)
        return ERROR_INT("&nout not defined", procName, 1);

    nleft = bb->n - bb->nwritten;
    nout = L_MIN(nleft, nbytes);
    *pnout = nout;

    if (nleft == 0) {
        bb->n = 0;
        bb->nwritten = 0;
        return 0;
    }


    memcpy(dest, (l_uint8 *)(bb->array + bb->nwritten), nout);
    bb->nwritten += nout;


    if (nout == nleft) {
        bb->n = 0;
        bb->nwritten = 0;
    }

    return 0;
}
