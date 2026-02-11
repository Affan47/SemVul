image_update_title(ImageWindow *imd)
{
	gchar *title = NULL;
	gchar *zoom = NULL;
	gchar *collection = NULL;

	if (!imd->top_window) return;

	if (imd->collection && collection_to_number(imd->collection) >= 0)
		{
		const gchar *name = imd->collection->name;
		if (!name) name = _("Untitled");
		collection = g_strdup_printf(_(" (Collection %s)"), name);
		}

	if (imd->title_show_zoom)
		{
		gchar *buf = image_zoom_get_as_text(imd);
		zoom = g_strconcat(" [", buf, "]", NULL);
		g_free(buf);
		}

	title = g_strdup_printf("%s%s%s%s%s%s",
		imd->title ? imd->title : "",
		imd->image_fd ? imd->image_fd->name : "",
		zoom ? zoom : "",
		collection ? collection : "",
		imd->image_fd ? " - " : "",
		imd->title_right ? imd->title_right : "");

	gtk_window_set_title(GTK_WINDOW(imd->top_window), title);

	g_free(title);
	g_free(zoom);
	g_free(collection);
}
