pixbuf_to_cairo (GOPixbuf *pixbuf)
{
	unsigned char *src, *dst;
	GOImage *image = GO_IMAGE (pixbuf);

	g_return_if_fail (GO_IS_PIXBUF (pixbuf) && image->data && pixbuf->pixbuf);

	src = gdk_pixbuf_get_pixels (pixbuf->pixbuf);
	dst = image->data;

	g_return_if_fail (gdk_pixbuf_get_rowstride (pixbuf->pixbuf) == (int) pixbuf->rowstride);

	go_cairo_convert_data_from_pixbuf (dst, src, image->width, image->height, pixbuf->rowstride);
}
