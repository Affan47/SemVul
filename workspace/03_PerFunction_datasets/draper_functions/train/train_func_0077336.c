writeBucket(CompiledFlowOutputPtr output)
{
    ComponentPtr c = output->component;
    FlowElementPtr flowEl = output->flowEl;
    AuUint8 *s, *d;
    AuUint32 size, bytesIn, bytesOut;
    AuBool overrun;

    if (flowEl->parmsChanged) {
        flowEl->write = c->data + flowEl->raw->exportbucket.offset *
                c->bytesPerSample;

        if (flowEl->countSamples)
            flowEl->numBytes = flowEl->raw->exportbucket.num_samples *
                    c->bytesPerSample;

        flowEl->parmsChanged = AuFalse;
    }

    s = flowEl->minibuf;
    d = flowEl->write;


    size = flowEl->minibufBytes;

    overrun = size > (c->dataEnd - d);

    if (flowEl->countSamples)
        size = aumin(size, flowEl->numBytes);


    bytesOut =
            (*output->rateConvert) (flowEl, s, d, c->dataEnd - d, size,
                                    &bytesIn);

    flowEl->write = d + bytesOut;
    flowEl->numBytes -= bytesOut;


    if (overrun)
        return AuChangeElementState(flowEl->flow, flowEl->elementNum,
                                    AuStateStop, AuFalse, AuReasonEOF);

    return AuFalse;
}
