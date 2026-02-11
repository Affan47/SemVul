pixDeskew(PIX     *pixs,
          l_int32  redsearch)
{
    PROCNAME("pixDeskew");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 1)
        return (PIX *)ERROR_PTR("pixs not 1 bpp", procName, NULL);
    if (redsearch != 1 && redsearch != 2 && redsearch != 4)
        return (PIX *)ERROR_PTR("redsearch not in {1,2,4}", procName, NULL);

    return pixFindSkewAndDeskew(pixs, redsearch, NULL, NULL);
}
