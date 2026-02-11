gdk_pixbuf_get_byte_length (const GdkPixbuf *pixbuf)
{
	g_return_val_if_fail (GDK_IS_PIXBUF (pixbuf), -1);

        return ((pixbuf->height - 1) * pixbuf->rowstride +
                pixbuf->width * ((pixbuf->n_channels * pixbuf->bits_per_sample + 7) / 8));
}
