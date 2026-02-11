nautilus_icon_info_new_for_icon_info (GtkIconInfo *icon_info,
				      gint         scale)
{
	NautilusIconInfo *icon;
	GdkPoint *points;
	gint n_points;
	const char *filename;
	char *basename, *p;

	icon = g_object_new (NAUTILUS_TYPE_ICON_INFO, NULL);

	icon->pixbuf = gtk_icon_info_load_icon (icon_info, NULL);

	icon->got_embedded_rect = gtk_icon_info_get_embedded_rect (icon_info,
								   &icon->embedded_rect);

	if (gtk_icon_info_get_attach_points (icon_info, &points, &n_points)) {
		icon->n_attach_points = n_points;
		icon->attach_points = points;
	}

	icon->display_name = g_strdup (gtk_icon_info_get_display_name (icon_info));

	filename = gtk_icon_info_get_filename (icon_info);
	if (filename != NULL) {
		basename = g_path_get_basename (filename);
		p = strrchr (basename, '.');
		if (p) {
			*p = 0;
		}
		icon->icon_name = basename;
	}

	icon->orig_scale = scale;

	return icon;
}
