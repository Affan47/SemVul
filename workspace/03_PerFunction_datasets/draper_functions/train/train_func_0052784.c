pixRenderPolygon(PTA      *ptas,
                 l_int32   width,
                 l_int32  *pxmin,
                 l_int32  *pymin)
{
l_float32  fxmin, fxmax, fymin, fymax;
PIX       *pixd;
PTA       *pta1, *pta2;

    PROCNAME("pixRenderPolygon");

    if (pxmin) *pxmin = 0;
    if (pymin) *pymin = 0;
    if (!ptas)
        return (PIX *)ERROR_PTR("ptas not defined", procName, NULL);


    if ((pta1 = generatePtaPolyline(ptas, width, 1, 0)) == NULL)
        return (PIX *)ERROR_PTR("pta1 not made", procName, NULL);
    if (width < 2)
        pta2 = convertPtaLineTo4cc(pta1);
    else
        pta2 = ptaClone(pta1);


    ptaGetRange(pta2, &fxmin, &fxmax, &fymin, &fymax);
    if (pxmin) *pxmin = (l_int32)(fxmin + 0.5);
    if (pymin) *pymin = (l_int32)(fymin + 0.5);
    pixd = pixCreate((l_int32)(fxmax + 0.5) + 1, (l_int32)(fymax + 0.5) + 1, 1);
    pixRenderPolyline(pixd, pta2, width, L_SET_PIXELS, 1);
    ptaDestroy(&pta1);
    ptaDestroy(&pta2);
    return pixd;
}
