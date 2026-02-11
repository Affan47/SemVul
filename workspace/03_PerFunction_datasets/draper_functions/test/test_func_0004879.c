nautilus_properties_window_drag_data_received (GtkWidget *widget, GdkDragContext *context,
					       int x, int y,
					       GtkSelectionData *selection_data,
					       guint info, guint time)
{
	char **uris;
	gboolean exactly_one;
	GtkImage *image;
 	GtkWindow *window;

	image = GTK_IMAGE (widget);
 	window = GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (image)));

	uris = g_strsplit ((const gchar *) gtk_selection_data_get_data (selection_data), "\r\n", 0);
	exactly_one = uris[0] != NULL && (uris[1] == NULL || uris[1][0] == '\0');


	if (!exactly_one) {
		eel_show_error_dialog
			(_("You cannot assign more than one custom icon at a time!"),
			 _("Please drag just one image to set a custom icon."),
			 window);
	} else {
		if (uri_is_local_image (uris[0])) {
			set_icon (uris[0], NAUTILUS_PROPERTIES_WINDOW (window));
		} else {
			GFile *f;

			f = g_file_new_for_uri (uris[0]);
			if (!g_file_is_native (f)) {
				eel_show_error_dialog
					(_("The file that you dropped is not local."),
					 _("You can only use local images as custom icons."),
					 window);

			} else {
				eel_show_error_dialog
					(_("The file that you dropped is not an image."),
					 _("You can only use local images as custom icons."),
					 window);
			}
			g_object_unref (f);
		}
	}
	g_strfreev (uris);
}
