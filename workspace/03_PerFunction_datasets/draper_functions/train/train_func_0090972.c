pixcompDestroy(PIXC  **ppixc)
{
PIXC  *pixc;

    PROCNAME("pixcompDestroy");

    if (!ppixc) {
        L_WARNING("ptr address is null!", procName);
        return;
    }

    if ((pixc = *ppixc) == NULL)
        return;

    FREE(pixc->data);
    if (pixc->text)
        FREE(pixc->text);
    FREE(pixc);
    *ppixc = NULL;
    return;
}
