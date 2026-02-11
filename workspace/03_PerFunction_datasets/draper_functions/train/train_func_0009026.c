add_icon (GtkIconFactory *factory,
	  const char *scalable_filename,
	  const char *sized_filename,
	  const char *stock_id)
{
	GtkIconSet *set = gtk_icon_set_new ();
	GtkIconSource *src = gtk_icon_source_new ();

	if (scalable_filename) {
		char *res = g_strconcat ("res:gnm:pixmaps/",
					 scalable_filename,
					 NULL);
		GdkPixbuf *pix = go_gdk_pixbuf_load_from_file (res);
		if (pix) {
			gtk_icon_source_set_size_wildcarded (src, TRUE);
			gtk_icon_source_set_pixbuf (src, pix);
			gtk_icon_set_add_source (set, src);
			g_object_unref (pix);
		} else {
			g_warning ("Missing resource %s\n", res);
		}
		g_free (res);
	}


	if (sized_filename && !scalable_filename) {
		char *res = g_strconcat ("res:gnm:pixmaps/",
					 sized_filename,
					 NULL);
		GdkPixbuf *pix = go_gdk_pixbuf_load_from_file (res);
		gtk_icon_source_set_size (src, GTK_ICON_SIZE_MENU);
		gtk_icon_source_set_size_wildcarded (src, FALSE);
		gtk_icon_source_set_pixbuf (src, pix);
		gtk_icon_set_add_source (set, src);
		g_object_unref (pix);
		g_free (res);
	}

	gtk_icon_factory_add (factory, stock_id, set);
	gtk_icon_set_unref (set);
	gtk_icon_source_free (src);
}
