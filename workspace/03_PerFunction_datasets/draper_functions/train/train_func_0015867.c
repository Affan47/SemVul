pixcompCreateFromPix(PIX     *pix,
                     l_int32  comptype)
{
size_t    size;
char     *text;
l_int32   ret, format;
l_uint8  *data;
PIXC     *pixc;

    PROCNAME("pixcompCreateFromPix");

    if (!pix)
        return (PIXC *)ERROR_PTR("pix not defined", procName, NULL);
    if (comptype != IFF_DEFAULT && comptype != IFF_TIFF_G4 &&
        comptype != IFF_PNG && comptype != IFF_JFIF_JPEG)
        return (PIXC *)ERROR_PTR("invalid comptype", procName, NULL);

    if ((pixc = (PIXC *)CALLOC(1, sizeof(PIXC))) == NULL)
        return (PIXC *)ERROR_PTR("pixc not made", procName, NULL);
    pixGetDimensions(pix, &pixc->w, &pixc->h, &pixc->d);
    pixGetResolution(pix, &pixc->xres, &pixc->yres);
    if (pixGetColormap(pix))
        pixc->cmapflag = 1;
    if ((text = pixGetText(pix)) != NULL)
        pixc->text = stringNew(text);

    pixcompDetermineFormat(comptype, pixc->d, pixc->cmapflag, &format);
    pixc->comptype = format;
    ret = pixWriteMem(&data, &size, pix, format);
    if (ret) {
        L_ERROR("write to memory failed", procName);
        pixcompDestroy(&pixc);
        return NULL;
    }
    pixc->data = data;
    pixc->size = (l_int32)size;

    return pixc;
}
