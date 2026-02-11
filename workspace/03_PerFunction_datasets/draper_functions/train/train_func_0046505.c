pixConvertTo32BySampling(PIX     *pixs,
                         l_int32  factor)
{
l_float32  scalefactor;
PIX       *pixt, *pixd;

    PROCNAME("pixConvertTo32BySampling");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (factor < 1)
        return (PIX *)ERROR_PTR("factor must be >= 1", procName, NULL);

    scalefactor = 1. / (l_float32)factor;
    pixt = pixScaleBySampling(pixs, scalefactor, scalefactor);
    pixd = pixConvertTo32(pixt);

    pixDestroy(&pixt);
    return pixd;
}
