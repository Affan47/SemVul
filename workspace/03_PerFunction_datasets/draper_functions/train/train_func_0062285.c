pixCopyColormap(PIX  *pixd,
                PIX  *pixs)
{
PIXCMAP  *cmaps, *cmapd;

    PROCNAME("pixCopyColormap");

    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    if (!pixd)
        return ERROR_INT("pixd not defined", procName, 1);

    if ((cmaps = pixGetColormap(pixs)) == NULL)
        return 0;

    if ((cmapd = pixcmapCopy(cmaps)) == NULL)
        return ERROR_INT("cmapd not made", procName, 1);
    pixSetColormap(pixd, cmapd);

    return 0;
}
