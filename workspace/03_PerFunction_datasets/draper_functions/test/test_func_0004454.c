pixAlphaBlendUniform(PIX      *pixs,
                     l_uint32  color)
{
PIX  *pixt, *pixd;

    PROCNAME("pixAlphaBlendUniform");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 32)
        return (PIX *)ERROR_PTR("pixs not 32 bpp", procName, NULL);

    pixt = pixCreateTemplate(pixs);
    pixSetAllArbitrary(pixt, color);
    pixd = pixBlendWithGrayMask(pixt, pixs, NULL, 0, 0);

    pixDestroy(&pixt);
    return pixd;
}
