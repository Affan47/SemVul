image_flip_x(gpaint_image *image)
{
    int width, height;
    GdkPixbuf *newpixbuf = gdk_pixbuf_new(
                            GDK_COLORSPACE_RGB,
                            TRUE,
                            gdk_pixbuf_get_bits_per_sample(image->pixbuf),
                            width = gdk_pixbuf_get_width(image->pixbuf),
                            height = gdk_pixbuf_get_height(image->pixbuf));
    int rowstride = gdk_pixbuf_get_rowstride(newpixbuf);
    int x, y;
    int j;
    unsigned char *p, *p2, *p3, *p4;
    int pixel_size = gdk_pixbuf_get_bits_per_sample(image->pixbuf) *
                        gdk_pixbuf_get_n_channels(image->pixbuf) / 8;

    g_assert(newpixbuf);
    for (p = gdk_pixbuf_get_pixels(newpixbuf), p2 = gdk_pixbuf_get_pixels(image->pixbuf), y = 0;
         y < height;
         y++, p += rowstride, p2 += rowstride)
    {
        p4 = p2 + pixel_size * (width - 1);
        p3 = p;
        for (x = 0; x < width; x++)
        {
	        for (j = 0; j < pixel_size; j++)
            {
	            *(p3 + j) = *(p4 + j);
            }
            p3 += pixel_size;
	        p4 -= pixel_size;
      }
    }
    gdk_pixbuf_unref(image->pixbuf);
    image->pixbuf = newpixbuf;
    return 0;
}
