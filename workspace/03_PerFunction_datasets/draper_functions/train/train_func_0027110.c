dpixCreate(l_int32  width,
           l_int32  height)
{
l_float64  *data;
l_uint64    bignum;
DPIX       *dpix;

    PROCNAME("dpixCreate");

    if (width <= 0)
        return (DPIX *)ERROR_PTR("width must be > 0", procName, NULL);
    if (height <= 0)
        return (DPIX *)ERROR_PTR("height must be > 0", procName, NULL);


    bignum = 8L * width * height;
    if (bignum > ((1LL << 31) - 1)) {
        L_ERROR("requested w = %d, h = %d\n", procName, width, height);
        return (DPIX *)ERROR_PTR("requested bytes >= 2^31", procName, NULL);
    }

    if ((dpix = (DPIX *)CALLOC(1, sizeof(DPIX))) == NULL)
        return (DPIX *)ERROR_PTR("CALLOC fail for dpix", procName, NULL);
    dpixSetDimensions(dpix, width, height);
    dpixSetWpl(dpix, width);
    dpix->refcount = 1;

    data = (l_float64 *)CALLOC(width * height, sizeof(l_float64));
    if (!data)
        return (DPIX *)ERROR_PTR("CALLOC fail for data", procName, NULL);
    dpixSetData(dpix, data);

    return dpix;
}
