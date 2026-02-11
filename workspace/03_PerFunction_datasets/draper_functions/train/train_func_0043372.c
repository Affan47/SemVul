pixEmbedForRotation(PIX       *pixs,
                    l_float32  angle,
                    l_int32    incolor,
                    l_int32    width,
                    l_int32    height)
{
l_int32    w, h, d, w1, h1, w2, h2, maxside, wnew, hnew, xoff, yoff, setcolor;
l_float64  sina, cosa, fw, fh;
PIX       *pixd;

    PROCNAME("pixEmbedForRotation");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (incolor != L_BRING_IN_WHITE && incolor != L_BRING_IN_BLACK)
        return (PIX *)ERROR_PTR("invalid incolor", procName, NULL);
    if (L_ABS(angle) < MIN_ANGLE_TO_ROTATE)
        return pixClone(pixs);


    pixGetDimensions(pixs, &w, &h, &d);
    maxside = (l_int32)(sqrt((l_float64)(width * width) +
                             (l_float64)(height * height)) + 0.5);
    if (w >= maxside && h >= maxside)
        return pixClone(pixs);


    cosa = cos(angle);
    sina = sin(angle);
    fw = (l_float64)w;
    fh = (l_float64)h;
    w1 = (l_int32)(L_ABS(fw * cosa - fh * sina) + 0.5);
    w2 = (l_int32)(L_ABS(-fw * cosa - fh * sina) + 0.5);
    h1 = (l_int32)(L_ABS(fw * sina + fh * cosa) + 0.5);
    h2 = (l_int32)(L_ABS(-fw * sina + fh * cosa) + 0.5);
    wnew = L_MAX(w, L_MAX(w1, w2));
    hnew = L_MAX(h, L_MAX(h1, h2));

    if ((pixd = pixCreate(wnew, hnew, d)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    pixCopyResolution(pixd, pixs);
    pixCopyColormap(pixd, pixs);
    pixCopySpp(pixd, pixs);
    pixCopyText(pixd, pixs);
    xoff = (wnew - w) / 2;
    yoff = (hnew - h) / 2;


    setcolor = (incolor == L_BRING_IN_BLACK) ? L_SET_BLACK : L_SET_WHITE;
    pixSetBlackOrWhite(pixd, setcolor);


    pixRasterop(pixd, xoff, yoff, w, h, PIX_SRC, pixs, 0, 0);
    return pixd;
}
