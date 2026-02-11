pixBlendInRect(PIX       *pixs,
               BOX       *box,
               l_uint32   val,
               l_float32  fract)
{
l_int32    i, j, bx, by, bw, bh, w, h, wpls;
l_int32    prval, pgval, pbval, rval, gval, bval;
l_uint32   val32;
l_uint32  *datas, *lines;

    PROCNAME("pixBlendInRect");

    if (!pixs || pixGetDepth(pixs) != 32)
        return ERROR_INT("pixs not defined or not 32 bpp", procName, 1);
    if (!box)
        return ERROR_INT("box not defined", procName, 1);

    boxGetGeometry(box, &bx, &by, &bw, &bh);
    pixGetDimensions(pixs, &w, &h, NULL);
    datas = pixGetData(pixs);
    wpls = pixGetWpl(pixs);
    extractRGBValues(val, &rval, &gval, &bval);
    for (i = 0; i < bh; i++) {
        if (by + i < 0 || by + i >= h) continue;
        lines = datas + (by + i) * wpls;
        for (j = 0; j < bw; j++) {
            if (bx + j < 0 || bx + j >= w) continue;
            val32 = *(lines + bx + j);
            extractRGBValues(val32, &prval, &pgval, &pbval);
            prval = (l_int32)((1. - fract) * prval + fract * rval);
            pgval = (l_int32)((1. - fract) * pgval + fract * gval);
            pbval = (l_int32)((1. - fract) * pbval + fract * bval);
            composeRGBPixel(prval, pgval, pbval, &val32);
            *(lines + bx + j) = val32;
        }
    }

    return 0;
}
