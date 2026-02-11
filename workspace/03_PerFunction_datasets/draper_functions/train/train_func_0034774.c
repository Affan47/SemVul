layout_status_update_image(LayoutWindow *lw)
{
	guint64 n;

	if (!layout_valid(&lw) || !lw->image) return;
	if (!lw->info_zoom || !lw->info_details) return;

	n = layout_list_count(lw, NULL);

	if (!n)
		{
		gtk_label_set_text(GTK_LABEL(lw->info_zoom), "");
		gtk_label_set_text(GTK_LABEL(lw->info_details), "");
		}
	else
		{
		gchar *text;
		gchar *b;

		text = image_zoom_get_as_text(lw->image);
		gtk_label_set_text(GTK_LABEL(lw->info_zoom), text);
		g_free(text);

		b = image_get_fd(lw->image) ? text_from_size(image_get_fd(lw->image)->size) : g_strdup("0");

		if (lw->image->unknown)
			{
			if (image_get_path(lw->image) && !access_file(image_get_path(lw->image), R_OK))
				{
				text = g_strdup_printf(_("(no read permission) %s bytes"), b);
				}
			else
				{
				text = g_strdup_printf(_("( ? x ? ) %s bytes"), b);
				}
			}
		else
			{
			gint width, height;

			image_get_image_size(lw->image, &width, &height);
			text = g_strdup_printf(_("( %d x %d ) %s bytes"),
					       width, height, b);
			}

		g_signal_emit_by_name (lw->image->pr, "update-pixel");

		g_free(b);

		gtk_label_set_text(GTK_LABEL(lw->info_details), text);
		g_free(text);
		}
	layout_util_sync_color(lw);
}
