pixDebugFlipDetect(const char *filename,
                   PIX        *pixs,
                   PIX        *pixhm,
                   l_int32     enable)
{
PIX  *pixt, *pixthm;

   if (!enable) return;


    pixt = pixConvert1To4Cmap(pixs);
    pixthm = pixMorphSequence(pixhm, "d5.5", 0);
    pixSetMaskedCmap(pixt, pixthm, 0, 0, 255, 0, 0);

    pixWrite(filename, pixt, IFF_PNG);
    pixDestroy(&pixthm);
    pixDestroy(&pixt);
    return;
}
