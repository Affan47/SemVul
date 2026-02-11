makeGaussianKernelSep(l_int32    halfheight,
                      l_int32    halfwidth,
                      l_float32  stdev,
                      l_float32  max,
                      L_KERNEL **pkelx,
                      L_KERNEL **pkely)
{
    PROCNAME("makeGaussianKernelSep");

    if (!pkelx || !pkely)
        return ERROR_INT("&kelx and &kely not defined", procName, 1);

    *pkelx = makeGaussianKernel(0, halfwidth, stdev, max);
    *pkely = makeGaussianKernel(halfheight, 0, stdev, 1.0);
    return 0;
}
