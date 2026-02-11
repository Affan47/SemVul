pixAffinePtaGray(PIX     *pixs,
                 PTA     *ptad,
                 PTA     *ptas,
                 l_uint8  grayval)
{
l_float32  *vc;
PIX        *pixd;

    PROCNAME("pixAffinePtaGray");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (!ptas)
        return (PIX *)ERROR_PTR("ptas not defined", procName, NULL);
    if (!ptad)
        return (PIX *)ERROR_PTR("ptad not defined", procName, NULL);
    if (pixGetDepth(pixs) != 8)
        return (PIX *)ERROR_PTR("pixs must be 8 bpp", procName, NULL);
    if (ptaGetCount(ptas) != 3)
        return (PIX *)ERROR_PTR("ptas count not 3", procName, NULL);
    if (ptaGetCount(ptad) != 3)
        return (PIX *)ERROR_PTR("ptad count not 3", procName, NULL);


    getAffineXformCoeffs(ptad, ptas, &vc);
    pixd = pixAffineGray(pixs, vc, grayval);
    FREE(vc);

    return pixd;
}
