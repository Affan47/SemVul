doSetup(flowEl, rateConverter, globalRate, isInput)
FlowElementPtr flowEl;
AuUint32(**rateConverter) (), globalRate;
AuBool isInput;
{
    AuUint32 elementRate;
    ComponentPtr c = flowEl->component;
    extern auConnSetup auSetup;

    if (!flowEl->setup) {
        AuInt32 format = c->format;

        flowEl->minibufChunk = c->minibufSize;
        flowEl->toNativeFormat = converters[format].toNativeFormat;
        flowEl->fromNativeFormat = converters[format].fromNativeFormat;

        if (flowEl->raw->type == AuElementTypeExportMonitor) {
            flowEl->toNativeFormat = flowEl->fromNativeFormat;
            flowEl->fromNativeFormat = (void (*)()) 0;
        } else if (sizeofFormat(format) == 1)
            flowEl->minibufChunk >>= 1;

        flowEl->setup = AuTrue;
    }

    if (flowEl->raw->type == AuElementTypeImportBucket ||
        flowEl->raw->type == AuElementTypeExportDevice)
        elementRate = flowEl->sampleRate;
    else if (flowEl->raw->type == AuElementTypeImportWaveForm) {
        AuUint32 integ, fract;

        elementRate = c->frequency;
        integ = elementRate / globalRate;
        fract = ((elementRate - (integ * globalRate)) << 16) / globalRate;
        flowEl->nextSample = (integ << 16) | fract;
    } else
        elementRate = c->sampleRate;


    if (!elementRate) {
        if (NasConfig.DoDebug > 10)
            osLogMsg("doSetup: elementRate == 0! Forcing to %d\n",
                     auSetup.minSampleRate);
        elementRate = auSetup.minSampleRate;
    }

    if (flowEl->raw->type != AuElementTypeImportWaveForm)
        flowEl->nextSample = isInput ? (elementRate << 16) / globalRate :
                (globalRate << 16) / elementRate;

    if (flowEl->raw->type == AuElementTypeExportMonitor) {
        if (c->numTracks == 1)
            *rateConverter = rcm_1;
        else if (c->numTracks == 2)
            *rateConverter = rcm_2;
        else
            *rateConverter = rcm_n;
    } else if (elementRate == globalRate)
        *rateConverter = rcNull;
    else if (c->bytesPerSample == 1)
        *rateConverter = rc_1;
    else if (c->bytesPerSample == 2)
        *rateConverter = rc_2;
    else if (c->bytesPerSample == 4)
        *rateConverter = rc_4;
    else
        *rateConverter = rc_n;
}
