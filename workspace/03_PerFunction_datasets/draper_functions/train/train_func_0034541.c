writeMonitor(CompiledFlowOutputPtr output)
{
    AuInt32 n;

    if ((n = (*output->rateConvert) (output->flowEl))) {
        ComponentPtr c = output->component;
        AuInt16 *s = (AuInt16 *) c->read;
        AuUint32 *p = (AuUint32 *) c->read;
        int i;


        if (output->flowEl->toNativeFormat)
            (*output->flowEl->toNativeFormat) (s, c->numTracks, n << 1);

        while (n--) {
            AuRequestMonitorNotifyEvent(output->flowEl, s);
            s += c->numTracks;
        }

        for (i = 0; i < (int) c->numTracks * auMinibufSamples; i++)
            *p++ = 0x7fff8001;

        c->write = c->read;
        return AuTrue;
    }

    return AuFalse;
}
