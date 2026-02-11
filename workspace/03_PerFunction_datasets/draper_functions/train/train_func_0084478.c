nemo_icon_view_screen_changed (GtkWidget *widget,
				   GdkScreen *previous_screen)
{
	NemoView *view;
	GList *files, *l;
	NemoFile *file;
	NemoDirectory *directory;
	NemoIconContainer *icon_container;

	if (GTK_WIDGET_CLASS (nemo_icon_view_parent_class)->screen_changed) {
		GTK_WIDGET_CLASS (nemo_icon_view_parent_class)->screen_changed (widget, previous_screen);
	}

	view = NEMO_VIEW (widget);
	if (NEMO_ICON_VIEW (view)->details->filter_by_screen) {
		icon_container = get_icon_container (NEMO_ICON_VIEW (view));

		directory = nemo_view_get_model (view);
		files = nemo_directory_get_file_list (directory);

		for (l = files; l != NULL; l = l->next) {
			file = l->data;

			if (!should_show_file_on_screen (view, file)) {
				nemo_icon_view_remove_file (view, file, directory);
			} else {
				if (nemo_icon_container_add (icon_container,
								 NEMO_ICON_CONTAINER_ICON_DATA (file))) {
					nemo_file_ref (file);
				}
			}
		}

		nemo_file_list_unref (files);
		g_list_free (files);
	}
}
