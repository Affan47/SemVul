supportedFormat(const QPixmap *pixmap)
{
    int depth = pixmap->depth();
    Visual *visual = (Visual*)pixmap->x11Info().visual();

    if (ImageByteOrder(pixmap->x11Info().display()) != LSBFirst)
        return false;


    if (pixmap->hasAlphaChannel())
        return true;


    if ((depth == 24 || depth == 32) &&
        visual->red_mask   == 0x00ff0000 &&
        visual->green_mask == 0x0000ff00 &&
        visual->blue_mask  == 0x000000ff)
    {
        return true;
    }


    if (depth == 16 &&
        visual->red_mask   == 0xf800 &&
        visual->green_mask == 0x07e0 &&
        visual->blue_mask  == 0x001f)
    {
        return true;
    }

    return false;
}
