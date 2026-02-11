UnrollFloatTo16(register _cmsTRANSFORM* info,
                                register cmsUInt16Number wIn[],
                                register cmsUInt8Number* accum,
                                register cmsUInt32Number Stride)
{

    int nChan      = T_CHANNELS(info -> InputFormat);
    int DoSwap     = T_DOSWAP(info ->InputFormat);
    int Reverse    = T_FLAVOR(info ->InputFormat);
    int SwapFirst  = T_SWAPFIRST(info -> InputFormat);
    int Extra      = T_EXTRA(info -> InputFormat);
    int ExtraFirst = DoSwap ^ SwapFirst;
    int Planar     = T_PLANAR(info -> InputFormat);
    cmsFloat32Number v;
    cmsUInt16Number  vi;
    int i, start = 0;
   cmsFloat64Number maximum = IsInkSpace(info ->InputFormat) ? 655.35 : 65535.0;


    if (ExtraFirst)
            start = Extra;

    for (i=0; i < nChan; i++) {

        int index = DoSwap ? (nChan - i - 1) : i;

        if (Planar)
            v = (cmsFloat32Number) ((cmsFloat32Number*) accum)[(i + start) * Stride];
        else
            v = (cmsFloat32Number) ((cmsFloat32Number*) accum)[i + start];

        vi = _cmsQuickSaturateWord(v * maximum);

        if (Reverse)
            vi = REVERSE_FLAVOR_16(vi);

        wIn[index] = vi;
    }


    if (Extra == 0 && SwapFirst) {
        cmsUInt16Number tmp = wIn[0];

        memmove(&wIn[0], &wIn[1], (nChan-1) * sizeof(cmsUInt16Number));
        wIn[nChan-1] = tmp;
    }

    if (T_PLANAR(info -> InputFormat))
        return accum + sizeof(cmsFloat32Number);
    else
        return accum + (nChan + Extra) * sizeof(cmsFloat32Number);
}
