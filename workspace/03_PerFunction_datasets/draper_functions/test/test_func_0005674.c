action_create_link_callback (GtkAction *action,
			     gpointer callback_data)
{
        NemoView *view;
        GList *selection;
        GArray *selected_item_locations;

        g_assert (NEMO_IS_VIEW (callback_data));

        view = NEMO_VIEW (callback_data);
	selection = nemo_view_get_selection (view);
	if (selection_not_empty_in_menu_callback (view, selection)) {
		selected_item_locations = nemo_view_get_selected_icon_locations (view);
	        nemo_view_create_links_for_files (view, selection, selected_item_locations);
	        g_array_free (selected_item_locations, TRUE);
	}

        nemo_file_list_free (selection);
}
