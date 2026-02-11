SendMonoRect(rfbClientPtr cl,
             int w,
             int h)
{
    int streamId = 1;
    int paletteLen, dataLen;

    if ( cl->ublen + TIGHT_MIN_TO_COMPRESS + 6 +
	 2 * cl->format.bitsPerPixel / 8 > UPDATE_BUF_SIZE ) {
        if (!rfbSendUpdateBuf(cl))
            return FALSE;
    }


    dataLen = (w + 7) / 8;
    dataLen *= h;

    cl->updateBuf[cl->ublen++] = (streamId | rfbTightExplicitFilter) << 4;
    cl->updateBuf[cl->ublen++] = rfbTightFilterPalette;
    cl->updateBuf[cl->ublen++] = 1;


    switch (cl->format.bitsPerPixel) {

    case 32:
        EncodeMonoRect32((uint8_t *)tightBeforeBuf, w, h);

        ((uint32_t *)tightAfterBuf)[0] = monoBackground;
        ((uint32_t *)tightAfterBuf)[1] = monoForeground;
        if (usePixelFormat24) {
            Pack24(cl, tightAfterBuf, &cl->format, 2);
            paletteLen = 6;
        } else
            paletteLen = 8;

        memcpy(&cl->updateBuf[cl->ublen], tightAfterBuf, paletteLen);
        cl->ublen += paletteLen;
        rfbStatRecordEncodingSentAdd(cl, rfbEncodingTight, 3 + paletteLen);
        break;

    case 16:
        EncodeMonoRect16((uint8_t *)tightBeforeBuf, w, h);

        ((uint16_t *)tightAfterBuf)[0] = (uint16_t)monoBackground;
        ((uint16_t *)tightAfterBuf)[1] = (uint16_t)monoForeground;

        memcpy(&cl->updateBuf[cl->ublen], tightAfterBuf, 4);
        cl->ublen += 4;
        rfbStatRecordEncodingSentAdd(cl, rfbEncodingTight, 7);
        break;

    default:
        EncodeMonoRect8((uint8_t *)tightBeforeBuf, w, h);

        cl->updateBuf[cl->ublen++] = (char)monoBackground;
        cl->updateBuf[cl->ublen++] = (char)monoForeground;
        rfbStatRecordEncodingSentAdd(cl, rfbEncodingTight, 5);
    }

    return CompressData(cl, streamId, dataLen,
                        tightConf[compressLevel].monoZlibLevel,
                        Z_DEFAULT_STRATEGY);
}
