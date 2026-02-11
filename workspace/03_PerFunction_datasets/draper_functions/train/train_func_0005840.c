_cmsComputeInterpParamsEx(cmsContext ContextID,
                                           const cmsUInt32Number nSamples[],
                                           int InputChan, int OutputChan,
                                           const void *Table,
                                           cmsUInt32Number dwFlags)
{
    cmsInterpParams* p;
    int i;


    if (InputChan > MAX_INPUT_DIMENSIONS) {
             cmsSignalError(ContextID, cmsERROR_RANGE, "Too many input channels (%d channels, max=%d)", InputChan, MAX_INPUT_DIMENSIONS);
            return NULL;
    }


    p = (cmsInterpParams*) _cmsMallocZero(ContextID, sizeof(cmsInterpParams));
    if (p == NULL) return NULL;


    p -> dwFlags  = dwFlags;
    p -> nInputs  = InputChan;
    p -> nOutputs = OutputChan;
    p ->Table     = Table;
    p ->ContextID  = ContextID;


    for (i=0; i < InputChan; i++) {

        p -> nSamples[i] = nSamples[i];
        p -> Domain[i]   = nSamples[i] - 1;
    }


    p -> opta[0] = p -> nOutputs;
    for (i=1; i < InputChan; i++)
        p ->opta[i] = p ->opta[i-1] * nSamples[InputChan-i];


    if (!_cmsSetInterpolationRoutine(p)) {
         cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "Unsupported interpolation (%d->%d channels)", InputChan, OutputChan);
        _cmsFree(ContextID, p);
        return NULL;
    }


    return p;
}
