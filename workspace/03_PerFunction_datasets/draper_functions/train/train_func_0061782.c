canvas_clipboard(gpaint_canvas *canvas)
{

    if (!clipboard)
    {
	GSList *list;

        clipboard = g_new0(gpaint_clipboard, 1);
        clipboard->image = 0;
        clipboard->points = point_array_new();


	g_object_set_data_full (G_OBJECT (canvas), GPAINT_CLIPBOARD_KEY,
				clipboard, (GDestroyNotify) canvas_clipboard_free);


        clipboard->pixbuf_formats =
		g_slist_sort (gdk_pixbuf_get_formats(),
				(GCompareFunc) canvas_clipboard_format_compare);
	for (list = clipboard->pixbuf_formats; list; list = g_slist_next (list))
	{
	    GdkPixbufFormat *format = list->data;

	    if (gdk_pixbuf_format_is_writable (format))
	    {
		gchar **mime_types;
		gchar **type;

		mime_types = gdk_pixbuf_format_get_mime_types (format);

		for (type = mime_types; *type; type++)
		    clipboard->n_target_entries++;

		g_strfreev (mime_types);
	    }
	}

	if (clipboard->n_target_entries > 0)
	{
	    gint i = 0;

	    clipboard->target_entries = g_new0(GtkTargetEntry,
						clipboard->n_target_entries);
	    clipboard->savers 	      = g_new0(gchar*,
						clipboard->n_target_entries + 1);

	    for (list = clipboard->pixbuf_formats; list; list = g_slist_next (list))
	    {
	        GdkPixbufFormat *format = list->data;

	        if (gdk_pixbuf_format_is_writable (format))
	        {
		    gchar *format_name;
		    gchar **mime_types;
		    gchar **type;

		    format_name = gdk_pixbuf_format_get_name (format);
		    mime_types = gdk_pixbuf_format_get_mime_types (format);

		    for (type = mime_types; *type; type++)
		    {
			gchar *mime_type = *type;

			clipboard->target_entries[i].target = g_strdup (mime_type);
			clipboard->target_entries[i].flags  = 0;
			clipboard->target_entries[i].info   = i;

			clipboard->savers[i]                = g_strdup (format_name);

			i++;
		    }

		    g_strfreev (mime_types);
		    g_free (format_name);
		}
	    }
	}
    }
    return clipboard;
}
