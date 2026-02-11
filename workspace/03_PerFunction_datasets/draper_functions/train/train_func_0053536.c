gth_browser_activate_action_file_print (GtkAction  *action,
					GthBrowser *browser)
{
	GList *items;
	GList *file_list;

	items = gth_file_selection_get_selected (GTH_FILE_SELECTION (gth_browser_get_file_list_view (browser)));
	file_list = gth_file_list_get_files (GTH_FILE_LIST (gth_browser_get_file_list (browser)), items);
	if (file_list != NULL) {
		cairo_surface_t  *current_image;
		GtkWidget        *viewer_page;
		GthImagePrintJob *print_job;
		GError           *error = NULL;

		current_image = NULL;
		viewer_page = gth_browser_get_viewer_page (browser);
		if ((gth_main_extension_is_active ("image_viewer"))
		    && (viewer_page != NULL)
		    && GTH_IS_IMAGE_VIEWER_PAGE (viewer_page))
		{
			GtkWidget *viewer;

			viewer = gth_image_viewer_page_get_image_viewer (GTH_IMAGE_VIEWER_PAGE (viewer_page));
			current_image = gth_image_viewer_get_current_image (GTH_IMAGE_VIEWER (viewer));
		}
		print_job = gth_image_print_job_new (file_list,
						     gth_browser_get_current_file (browser),
						     current_image,
						     g_file_info_get_display_name (gth_browser_get_location_data (browser)->info),
						     &error);

		if (print_job != NULL) {
			gth_image_print_job_run (print_job,
						 GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
						 browser);
		}
		else {
			_gtk_error_dialog_from_gerror_show (GTK_WINDOW (browser), _("Could not print the selected files"), error);
			g_clear_error (&error);
		}
	}

	_g_object_list_unref (file_list);
	_gtk_tree_path_list_free (items);
}
