pixDestroy(PIX  **ppix)
{
PIX  *pix;

    PROCNAME("pixDestroy");

    if (!ppix) {
        L_WARNING("ptr address is null!", procName);
        return;
    }

    if ((pix = *ppix) == NULL)
        return;

    pixFree(pix);
    *ppix = NULL;
    return;
}
