pixCreateTemplate(PIX  *pixs)
{
PIX  *pixd;

    PROCNAME("pixCreateTemplate");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);

    if ((pixd = pixCreateTemplateNoInit(pixs)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    memset(pixd->data, 0, 4 * pixd->wpl * pixd->h);
    return pixd;
}
