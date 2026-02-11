numaGammaTRC(l_float32  gamma,
             l_int32    minval,
             l_int32    maxval)
{
l_int32    i, val;
l_float32  x, invgamma;
NUMA      *na;

    PROCNAME("numaGammaTRC");

    if (minval >= maxval)
        return (NUMA *)ERROR_PTR("minval not < maxval", procName, NULL);
    if (gamma <= 0.0) {
        L_WARNING("gamma must be > 0.0; setting to 1.0", procName);
        gamma = 1.0;
    }

    invgamma = 1. / gamma;
    na = numaCreate(256);
    for (i = 0; i < minval; i++)
        numaAddNumber(na, 0);
    for (i = minval; i <= maxval; i++) {
        if (i < 0) continue;
        if (i > 255) continue;
        x = (l_float32)(i - minval) / (l_float32)(maxval - minval);
        val = (l_int32)(255. * powf(x, invgamma) + 0.5);
        val = L_MAX(val, 0);
        val = L_MIN(val, 255);
        numaAddNumber(na, val);
    }
    for (i = maxval + 1; i < 256; i++)
        numaAddNumber(na, 255);

    return na;
}
