affineXformSampledPt(l_float32  *vc,
                     l_int32     x,
                     l_int32     y,
                     l_int32    *pxp,
                     l_int32    *pyp)
{
    PROCNAME("affineXformSampledPt");

    if (!vc)
        return ERROR_INT("vc not defined", procName, 1);

    *pxp = (l_int32)(vc[0] * x + vc[1] * y + vc[2] + 0.5);
    *pyp = (l_int32)(vc[3] * x + vc[4] * y + vc[5] + 0.5);
    return 0;
}
