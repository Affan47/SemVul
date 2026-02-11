pixelShiftByComponent(l_int32    rval,
                      l_int32    gval,
                      l_int32    bval,
                      l_uint32   srcval,
                      l_uint32   dstval,
                      l_uint32  *ppixel)
{
l_int32  rsval, rdval, gsval, gdval, bsval, bdval, rs, gs, bs;

    PROCNAME("pixelShiftByComponent");

    if (!ppixel)
        return ERROR_INT("&pixel defined", procName, 1);

    extractRGBValues(srcval, &rsval, &gsval, &bsval);
    extractRGBValues(dstval, &rdval, &gdval, &bdval);
    if (rdval == rsval)
        rs = rval;
    else if (rdval < rsval)
        rs = (rval * rdval) / rsval;
    else
        rs = 255 - (255 - rdval) * (255 - rval) / (255 - rsval);
    if (gdval == gsval)
        gs = gval;
    else if (gdval < gsval)
        gs = (gval * gdval) / gsval;
    else
        gs = 255 - (255 - gdval) * (255 - gval) / (255 - gsval);
    if (bdval == bsval)
        bs = bval;
    else if (bdval < bsval)
        bs = (bval * bdval) / bsval;
    else
        bs = 255 - (255 - bdval) * (255 - bval) / (255 - bsval);
    composeRGBPixel(rs, gs, bs, ppixel);
    return 0;
}
