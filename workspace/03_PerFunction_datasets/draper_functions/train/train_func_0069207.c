writePhysicalOutputsStereo(void)
{
    AuBlock l;
    void *buf;
    int bufSize;

    if (sndStatOut.isStereo) {
        buf = stereoOutputDevice->minibuf;
        bufSize = stereoOutputDevice->bytesPerSample
                * stereoOutputDevice->minibufSamples;
    } else {
        switch (stereoOutputDevice->format) {
        case AuFormatLinearSigned16LSB:
            stereoToMonoLinearSigned16LSB(stereoOutputDevice->
                                          minibufSamples);
            break;

        case AuFormatLinearUnsigned8:
            stereoToMonoLinearUnsigned8(stereoOutputDevice->
                                        minibufSamples);
            break;

        default:

            assert(0);
        }

        buf = monoOutputDevice->minibuf;
        bufSize = monoOutputDevice->bytesPerSample
                * stereoOutputDevice->minibufSamples;
    }

    l = AuBlockAudio();
    write(sndStatOut.fd, buf, bufSize);

#ifdef DEBUGDSPOUT
    {
        char tempbuf[80];

        snprintf(tempbuf, sizeof tempbuf, "\nwriteStereo buf: %d size: %d\n",
                 buf, bufSize);
        write(dspout, tempbuf, strlen(tempbuf));
        write(dspout, buf, bufSize);
    }
#endif

    AuUnBlockAudio(l);
}
