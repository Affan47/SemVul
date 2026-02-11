papertape_unrealize(GtkWidget *widget)
{
	Papertape *tape;

	g_return_if_fail(widget != NULL);
	g_return_if_fail(IS_PAPERTAPE(widget));

	tape = PAPERTAPE(widget);

	if (tape->idlefunc)
		gtk_idle_remove(tape->idlefunc);
	tape->idlefunc = 0;

	if (tape->pixmap)
		gdk_pixmap_unref(tape->pixmap);
	tape->pixmap = NULL;

	g_free(tape->pixbuf);
	tape->pixbuf = NULL;

	if (tape->mutex)
		g_mutex_free(tape->mutex);
	tape->mutex = NULL;

	if (GTK_WIDGET_CLASS(parent_class)->unrealize)
		(*GTK_WIDGET_CLASS(parent_class)->unrealize)(widget);
}
