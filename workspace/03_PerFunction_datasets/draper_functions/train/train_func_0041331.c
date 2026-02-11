rgbMapToGdkPixbuf(RgbMap *rgbMap)
{
    if (!rgbMap)
        return NULL;

    guchar *pixdata = (guchar *)
          malloc(sizeof(guchar) * rgbMap->width * rgbMap->height * 3);
    if (!pixdata)
        return NULL;

    int n_channels = 3;
    int rowstride  = rgbMap->width * 3;

    GdkPixbuf *buf = gdk_pixbuf_new_from_data(pixdata, GDK_COLORSPACE_RGB,
                        0, 8, rgbMap->width, rgbMap->height,
                        rowstride, NULL, NULL);


    int x,y;
    int row  = 0;
    for (y=0 ; y<rgbMap->height ; y++)
        {
        guchar *p = pixdata + row;
        for (x=0 ; x<rgbMap->width ; x++)
            {
            RGB rgb = rgbMap->getPixel(rgbMap, x, y);
            p[0] = rgb.r & 0xff;
            p[1] = rgb.g & 0xff;
            p[2] = rgb.b & 0xff;
            p += n_channels;
            }
        row += rowstride;
        }

    return buf;
}
