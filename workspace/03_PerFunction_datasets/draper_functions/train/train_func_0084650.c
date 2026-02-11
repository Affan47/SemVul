requested_folder_attributes_ready_cb (GObject  *file_source,
				      GError   *error,
				      gpointer  user_data)
{
	LoadData   *load_data = user_data;
	GthBrowser *browser = load_data->browser;

	if (error != NULL) {
		load_data_error (load_data, error);
		load_data_free (load_data);
		return;
	}

	gth_file_data_set_info (browser->priv->location, load_data->requested_folder->info);

	browser->priv->current_sort_type = gth_main_get_sort_type (g_file_info_get_attribute_string (browser->priv->location->info, "sort::type"));
	browser->priv->current_sort_inverse = g_file_info_get_attribute_boolean (browser->priv->location->info, "sort::inverse");
	if (browser->priv->current_sort_type == NULL) {
		browser->priv->current_sort_type = browser->priv->default_sort_type;
		browser->priv->current_sort_inverse = browser->priv->default_sort_inverse;
		g_file_info_set_attribute_string (browser->priv->location->info, "sort::type", browser->priv->current_sort_type->name);
		g_file_info_set_attribute_boolean (browser->priv->location->info, "sort::inverse", browser->priv->current_sort_inverse);
	}
	_gth_browser_set_sort_order (browser, browser->priv->current_sort_type, browser->priv->current_sort_inverse, FALSE);

	gth_file_source_list (load_data->file_source,
			      load_data->requested_folder->file,
			      _gth_browser_get_fast_file_type (browser, load_data->requested_folder->file) ? GFILE_STANDARD_ATTRIBUTES_WITH_FAST_CONTENT_TYPE : GFILE_STANDARD_ATTRIBUTES_WITH_CONTENT_TYPE,
			      _gth_browser_load_ready_cb,
			      load_data);
}
