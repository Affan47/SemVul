button_data_file_changed (NemoFile *file,
			  ButtonData *button_data)
{
	GFile *location, *current_location, *parent, *button_parent;
	ButtonData *current_button_data;
	char *display_name;
	NemoPathBar *path_bar;
	gboolean renamed, child;

	path_bar = (NemoPathBar *) gtk_widget_get_ancestor (button_data->button,
								NEMO_TYPE_PATH_BAR);
	if (path_bar == NULL) {
		return;
	}

	g_assert (path_bar->current_path != NULL);
	g_assert (path_bar->current_button_data != NULL);

	current_button_data = path_bar->current_button_data;

	location = nemo_file_get_location (file);
	if (!g_file_equal (button_data->path, location)) {
		parent = g_file_get_parent (location);
		button_parent = g_file_get_parent (button_data->path);

		renamed = (parent != NULL && button_parent != NULL) &&
			   g_file_equal (parent, button_parent);

		if (parent != NULL) {
			g_object_unref (parent);
		}
		if (button_parent != NULL) {
			g_object_unref (button_parent);
		}

		if (renamed) {
			button_data->path = g_object_ref (location);
		} else {


			child = g_file_has_prefix (button_data->path,
						   path_bar->current_path);

			if (child) {

				g_object_unref (location);
				location = g_file_get_parent (button_data->path);
				current_location = g_object_ref (path_bar->current_path);
			} else {


				current_location = nemo_file_get_location (current_button_data->file);
			}

        		nemo_path_bar_update_path (path_bar, location, FALSE);
        		nemo_path_bar_set_path (path_bar, current_location);
			g_object_unref (location);
			g_object_unref (current_location);
			return;
		}
	} else if (nemo_file_is_gone (file)) {
		gint idx, position;


		current_location = nemo_file_get_location (current_button_data->file);

		if (g_file_has_prefix (location, current_location)) {

			position = g_list_position (path_bar->button_list,
						    g_list_find (path_bar->button_list, button_data));

			if (position != -1) {
				for (idx = 0; idx <= position; idx++) {
					gtk_container_remove (GTK_CONTAINER (path_bar),
							      BUTTON_DATA (path_bar->button_list->data)->button);
				}
			}
		}

		g_object_unref (current_location);
		g_object_unref (location);
		return;
	}
	g_object_unref (location);


	if (button_data->type != MOUNT_BUTTON) {
		display_name = nemo_file_get_display_name (file);
		if (g_strcmp0 (display_name, button_data->dir_name) != 0) {
			g_free (button_data->dir_name);
			button_data->dir_name = g_strdup (display_name);
		}

		g_free (display_name);
	}
	nemo_path_bar_update_button_appearance (button_data);
}
