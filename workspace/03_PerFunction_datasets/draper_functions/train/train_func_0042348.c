plugin_extensions(G3DContext *context)
{
	gchar *extensions = g_strdup("");
	gchar **retval;
	gchar *tmp;
	gchar *ext;
	gchar **exts;
	GSList *fitem;
	GSList *list;
	GdkPixbufFormat *format;

	list = fitem = gdk_pixbuf_get_formats();
	while(fitem)
	{
		format = (GdkPixbufFormat *)fitem->data;
		exts = gdk_pixbuf_format_get_extensions(format);
		ext = g_strjoinv(":", exts);
		tmp = g_strdup_printf("%s%s%s", extensions,
				      strlen(extensions) ? ":" : "",
				      ext);
		g_strfreev(exts);
		g_free(ext);
		g_free(extensions);
		extensions = tmp;
		fitem = fitem->next;
	}

	retval = g_strsplit(extensions, ":", 0);
	g_free(extensions);
	g_slist_free(list);

	return retval;
}
