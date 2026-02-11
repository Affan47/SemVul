PrepareRowForImg24(rfbClientPtr cl,
                    uint8_t *dst,
                    int x,
                    int y,
                    int count)
{
    uint32_t *fbptr;
    uint32_t pix;

    fbptr = (uint32_t *)
        &cl->scaledScreen->frameBuffer[y * cl->scaledScreen->paddedWidthInBytes + x * 4];

    while (count--) {
        pix = *fbptr++;
        *dst++ = (uint8_t)(pix >> cl->screen->serverFormat.redShift);
        *dst++ = (uint8_t)(pix >> cl->screen->serverFormat.greenShift);
        *dst++ = (uint8_t)(pix >> cl->screen->serverFormat.blueShift);
    }
}
