createMonitor(AuUint32 format, AuUint32 numTracks)
{
    ComponentPtr c;
    AuUint32 minibufSize;

    minibufSize = auNativeBytesPerSample * auMinibufSamples * numTracks;


    if (!(c = (ComponentPtr) aualloc(PAD4(sizeof(ComponentRec)) +
                                     PAD4(minibufSize) * 4)))
        return NULL;

    c->format = format;
    c->numTracks = numTracks;
    c->refCnt = 0;
    c->minibuf = (AuUint8 *) c + PAD4(sizeof(ComponentRec));
    c->read = c->minibuf + PAD4(minibufSize) * 2;
    c->minibufSize = minibufSize;
    c->physicalDeviceMask = NotAPhysicalDevice;
    c->kind = AuComponentKindOther;
    c->bytesPerSample = c->numTracks * sizeofFormat(c->format);

    return c;
}
