ptaScale(PTA       *ptas,
         l_float32  scalex,
         l_float32  scaley)
{
l_int32    i, npts;
l_float32  x, y;
PTA       *ptad;

    PROCNAME("ptaScale");

    if (!ptas)
        return (PTA *)ERROR_PTR("ptas not defined", procName, NULL);

    npts = ptaGetCount(ptas);
    if ((ptad = ptaCreate(npts)) == NULL)
        return (PTA *)ERROR_PTR("ptad not made", procName, NULL);
    for (i = 0; i < npts; i++) {
        ptaGetPt(ptas, i, &x, &y);
        ptaAddPt(ptad, scalex * x, scaley * y);
    }

    return ptad;
}
