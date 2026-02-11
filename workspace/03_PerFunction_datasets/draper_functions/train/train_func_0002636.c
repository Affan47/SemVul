gth_file_tool_resize_destroy_options (GthFileTool *base)
{
	GthFileToolResize *self;
	GtkWidget         *window;
	GtkWidget         *viewer_page;
	GtkWidget         *viewer;
	GSettings         *viewer_settings;

	self = (GthFileToolResize *) base;

	if (self->priv->update_size_id != 0) {
		g_source_remove (self->priv->update_size_id);
		self->priv->update_size_id = 0;
	}

	if (self->priv->builder != NULL) {
		int unit;


		unit = gtk_combo_box_get_active (GTK_COMBO_BOX (GET_WIDGET ("unit_combobox")));
		g_settings_set_enum (self->priv->settings, PREF_RESIZE_UNIT, unit);
		g_settings_set_double (self->priv->settings, PREF_RESIZE_WIDTH, (float) gtk_spin_button_get_value (GTK_SPIN_BUTTON (GET_WIDGET ("resize_width_spinbutton"))));
		g_settings_set_double (self->priv->settings, PREF_RESIZE_HEIGHT, (float) gtk_spin_button_get_value (GTK_SPIN_BUTTON (GET_WIDGET ("resize_height_spinbutton"))));
		g_settings_set_int (self->priv->settings, PREF_RESIZE_ASPECT_RATIO_WIDTH, gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (GET_WIDGET ("ratio_w_spinbutton"))));
		g_settings_set_int (self->priv->settings, PREF_RESIZE_ASPECT_RATIO_HEIGHT, gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (GET_WIDGET ("ratio_h_spinbutton"))));
		g_settings_set_enum (self->priv->settings, PREF_RESIZE_ASPECT_RATIO, gtk_combo_box_get_active (GTK_COMBO_BOX (self->priv->ratio_combobox)));
		g_settings_set_boolean (self->priv->settings, PREF_RESIZE_ASPECT_RATIO_INVERT, gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (GET_WIDGET ("invert_ratio_checkbutton"))));
		g_settings_set_boolean (self->priv->settings, PREF_RESIZE_HIGH_QUALITY, gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (GET_WIDGET ("high_quality_checkbutton"))));


		_cairo_clear_surface (&self->priv->new_image);
		_cairo_clear_surface (&self->priv->original_image);
		_g_clear_object (&self->priv->builder);
	}

	window = gth_file_tool_get_window (GTH_FILE_TOOL (self));
	viewer_page = gth_browser_get_viewer_page (GTH_BROWSER (window));
	viewer = gth_image_viewer_page_get_image_viewer (GTH_IMAGE_VIEWER_PAGE (viewer_page));
	gth_image_viewer_set_tool (GTH_IMAGE_VIEWER (viewer), NULL);


	viewer_settings = g_settings_new (GTHUMB_IMAGE_VIEWER_SCHEMA);
	gth_image_viewer_set_zoom_quality (GTH_IMAGE_VIEWER (viewer),
					   g_settings_get_enum (viewer_settings, PREF_IMAGE_VIEWER_ZOOM_QUALITY));

	g_object_unref (viewer_settings);
}
