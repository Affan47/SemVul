pixSwapAndDestroy(PIX  **ppixd,
                  PIX  **ppixs)
{
    PROCNAME("pixSwapAndDestroy");

    if (!ppixd)
        return ERROR_INT("&pixd not defined", procName, 1);
    if (!ppixs)
        return ERROR_INT("&pixs not defined", procName, 1);
    if (*ppixs == NULL)
        return ERROR_INT("pixs not defined", procName, 1);
    if (ppixs == ppixd)
        return ERROR_INT("&pixd == &pixs", procName, 1);

    pixDestroy(ppixd);
    *ppixd = pixClone(*ppixs);
    pixDestroy(ppixs);
    return 0;
}
