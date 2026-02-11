spinner_new(const gchar *path, gint interval)
{
	SpinnerData *sp;

	sp = g_new0(SpinnerData, 1);

	if (path)
		{
		gchar *pathl;
		GdkPixbuf *pb;
		gint n;
		gchar *buf;

		pathl = path_from_utf8(path);

		n = 0;
		buf = g_strdup_printf("%s%02d.png", pathl, n);
		while ((pb = gdk_pixbuf_new_from_file(buf, NULL)))
			{
			sp->list = g_list_append(sp->list, pb);

			n++;
			g_free(buf);
			buf = g_strdup_printf("%s%02d.png", pathl, n);
			}
		g_free(buf);

		g_free(pathl);
		}

	if (!sp->list)
		{
		GdkPixbuf *pb;
		gint n;
		gint w, h;

		pb = gdk_pixbuf_new_from_inline(-1, icon_spinner, FALSE, NULL);
		w = gdk_pixbuf_get_width(pb);
		h = gdk_pixbuf_get_height(pb) / SPINNER_FRAMES;
		for (n = 0; n < SPINNER_FRAMES; n++)
			{
			sp->list = g_list_append(sp->list,
						 gdk_pixbuf_new_subpixbuf(pb, 0, n * h, w, h));
			}

		g_object_unref(pb);
		}

	if (sp->list)
		{
		GdkPixbuf *pb;

		pb = sp->list->data;
		sp->image = gtk_image_new_from_pixbuf(pb);
		}
	else
		{
		sp->image = gtk_image_new_from_stock(GTK_STOCK_MISSING_IMAGE, GTK_ICON_SIZE_DIALOG);
		}

	g_object_set_data(G_OBJECT(sp->image), "spinner", sp);

	g_signal_connect(G_OBJECT(sp->image), "destroy",
			 G_CALLBACK(spinner_destroy_cb), sp);

	spinner_set_timeout(sp, interval);

	return sp->image;
}
