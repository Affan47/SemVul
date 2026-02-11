pixMeasureSaturation(PIX        *pixs,
                     l_int32     factor,
                     l_float32  *psat)
{
l_int32    w, h, d, i, j, wpl, sum, count;
l_int32    rval, gval, bval, hval, sval, vval;
l_uint32  *data, *line;

    PROCNAME("pixMeasureSaturation");

    if (!psat)
        return ERROR_INT("pixs not defined", procName, 1);
    *psat = 0.0;
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 32)
        return ERROR_INT("pixs not 32 bpp", procName, 1);
    if (factor < 1)
        return ERROR_INT("subsampling factor < 1", procName, 1);

    data = pixGetData(pixs);
    wpl = pixGetWpl(pixs);
    for (i = 0, sum = 0, count = 0; i < h; i += factor) {
        line = data + i * wpl;
        for (j = 0; j < w; j += factor) {
            extractRGBValues(line[j], &rval, &gval, &bval);
            convertRGBToHSV(rval, gval, bval, &hval, &sval, &vval);
            sum += sval;
            count++;
        }
    }

    if (count > 0)
        *psat = (l_float32)sum / (l_float32)count;
    return 0;
}
