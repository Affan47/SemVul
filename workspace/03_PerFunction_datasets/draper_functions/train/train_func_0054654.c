papertape_copy_data(Papertape *dst, Papertape *src)
{
	GtkWidget *srcwidget, *dstwidget;
	gint srcsize, dstsize;

	g_return_if_fail(dst != NULL);
	g_return_if_fail(src != NULL);
	g_return_if_fail(IS_PAPERTAPE(dst));
	g_return_if_fail(IS_PAPERTAPE(src));
	g_return_if_fail(dst->pixbuf != NULL);
	g_return_if_fail(src->pixbuf != NULL);

	dstwidget = GTK_WIDGET(dst);
	srcwidget = GTK_WIDGET(src);

	srcsize = srcwidget->allocation.width * srcwidget->allocation.height;
	dstsize = dstwidget->allocation.width * dstwidget->allocation.height;

	g_return_if_fail(dstsize == srcsize);

	memcpy(dst->pixbuf, src->pixbuf, dstsize * sizeof(guchar));

	set_idle_callback(dst);
}
