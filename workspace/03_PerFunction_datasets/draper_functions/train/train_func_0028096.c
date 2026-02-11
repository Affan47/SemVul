PrecalculatedXFORMGamutCheck(_cmsTRANSFORM* p,
                                  const void* in,
                                  void* out, cmsUInt32Number Size)
{
    cmsUInt8Number* accum;
    cmsUInt8Number* output;
    cmsUInt16Number wIn[cmsMAXCHANNELS], wOut[cmsMAXCHANNELS];
    cmsUInt32Number i, n;

    accum  = (cmsUInt8Number*)  in;
    output = (cmsUInt8Number*)  out;
    n = Size;

    for (i=0; i < n; i++) {

        accum = p -> FromInput(p, wIn, accum, Size);
        TransformOnePixelWithGamutCheck(p, wIn, wOut);
        output = p -> ToOutput(p, wOut, output, Size);
    }
}
