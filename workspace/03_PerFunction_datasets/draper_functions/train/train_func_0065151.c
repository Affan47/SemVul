convertRGBToYUV(l_int32   rval,
                l_int32   gval,
                l_int32   bval,
                l_int32  *pyval,
                l_int32  *puval,
                l_int32  *pvval)
{
l_float32  norm;

    PROCNAME("convertRGBToYUV");

    if (!pyval || !puval || !pvval)
        return ERROR_INT("&yval, &uval, &vval not all defined", procName, 1);

    norm = 1.0 / 256.;
    *pyval = (l_int32)(16.0 +
                norm * (65.738 * rval + 129.057 * gval + 25.064 * bval) + 0.5);
    *puval = (l_int32)(128.0 +
                norm * (-37.945 * rval -74.494 * gval + 112.439 * bval) + 0.5);
    *pvval = (l_int32)(128.0 +
                norm * (112.439 * rval - 94.154 * gval - 18.285 * bval) + 0.5);
    return 0;
}
