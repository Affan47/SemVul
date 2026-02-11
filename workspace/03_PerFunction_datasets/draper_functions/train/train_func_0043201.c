convertBINARY(int *imDepth, uchar **outbuf)
{
    uchar *p, *q, *end;

    dbgprintf("Pixel type is binary\n");
    if (currImgNbSamples >= 1) {

        *imDepth = 1;
        *outbuf = new uchar[(long)currImgWidth * (long)currImgHeight];
        p = *outbuf;
        q = (uchar *)(currBuffp[currComp]) + buffZOffset;
        end = p + (long)currImgWidth * (long)currImgHeight;
        while (p != end)
            *p++ = (*q++) ? 0 :  255;
        if ((currImgNbSamples == 1) && (currImgThickness == 1)) {

            freeCurrentBuffers();
        } else {
            dbgprintf("There are %d binary buffers in this image\n", currImgNbSamples);

        }
    } else {
        errprintf("Incorrect file: %d sample!\n", currImgNbSamples);
        freeCurrentBuffers();
    }

    return;
}
