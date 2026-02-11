PackChunkyFloatsFromFloat(_cmsTRANSFORM* info,
                                          cmsFloat32Number wOut[],
                                          cmsUInt8Number* output,
                                          cmsUInt32Number Stride)
{
    int nChan      = T_CHANNELS(info -> OutputFormat);
    int DoSwap     = T_DOSWAP(info ->OutputFormat);
    int Reverse    = T_FLAVOR(info ->OutputFormat);
    int Extra      = T_EXTRA(info -> OutputFormat);
    int SwapFirst  = T_SWAPFIRST(info -> OutputFormat);
    int ExtraFirst = DoSwap && !SwapFirst;
    cmsFloat64Number maximum = IsInkSpace(info ->OutputFormat) ? 100.0 : 1.0;
    cmsFloat32Number* swap1;
    cmsFloat64Number v = 0;
    int i;

    swap1 = (cmsFloat32Number*) output;

    if (ExtraFirst) {
        output += Extra * sizeof(cmsFloat32Number);
    }

    for (i=0; i < nChan; i++) {

        int index = DoSwap ? (nChan - i - 1) : i;

        v = wOut[index] * maximum;

        if (Reverse)
            v = maximum - v;

        *(cmsFloat32Number*) output = (cmsFloat32Number) v;

        output += sizeof(cmsFloat32Number);
    }

    if (!ExtraFirst) {
        output += Extra * sizeof(cmsFloat32Number);
    }

    if (Extra == 0 && SwapFirst) {

        memmove(swap1 + 1, swap1, (nChan-1)* sizeof(cmsFloat32Number));
        *swap1 = (cmsFloat32Number) v;
    }


    return output;
}
