pixMultConstAccumulate(PIX       *pixs,
                       l_float32  factor,
                       l_uint32   offset)
{
l_int32    w, h, wpl;
l_uint32  *data;

    PROCNAME("pixMultConstAccumulate");

    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    if (pixGetDepth(pixs) != 32)
        return ERROR_INT("pixs not 32 bpp", procName, 1);
    if (offset > 0x40000000)
        offset = 0x40000000;

    pixGetDimensions(pixs, &w, &h, NULL);
    data = pixGetData(pixs);
    wpl = pixGetWpl(pixs);

    multConstAccumulateLow(data, w, h, wpl, factor, offset);
    return 0;
}
