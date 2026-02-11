pixConvertForPSWrap(PIX  *pixs)
{
l_int32   d;
PIX      *pixd;
PIXCMAP  *cmap;

    PROCNAME("pixConvertForPSWrap");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);

    cmap = pixGetColormap(pixs);
    d = pixGetDepth(pixs);
    switch (d)
    {
    case 1:
    case 32:
        pixd = pixClone(pixs);
        break;
    case 2:
        if (cmap)
            pixd = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);
        else
            pixd = pixConvert2To8(pixs, 0, 0x55, 0xaa, 0xff, FALSE);
        break;
    case 4:
        if (cmap)
            pixd = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);
        else
            pixd = pixConvert4To8(pixs, FALSE);
        break;
    case 8:
        pixd = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);
        break;
    case 16:
        pixd = pixConvert16To8(pixs, 1);
        break;
    default:
        fprintf(stderr, "depth not in {1, 2, 4, 8, 16, 32}");
        return NULL;
   }

   return pixd;
}
