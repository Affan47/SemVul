fpixaSetPixel(FPIXA     *fpixa,
              l_int32    index,
              l_int32    x,
              l_int32    y,
              l_float32  val)
{
l_int32  n, ret;
FPIX    *fpix;

    PROCNAME("fpixaSetPixel");

    if (!fpixa)
        return ERROR_INT("fpixa not defined", procName, 1);
    n = fpixaGetCount(fpixa);
    if (index < 0 || index >= n)
        return ERROR_INT("invalid index into fpixa", procName, 1);

    fpix = fpixaGetFPix(fpixa, index, L_CLONE);
    ret = fpixSetPixel(fpix, x, y, val);
    fpixDestroy(&fpix);
    return ret;
}
