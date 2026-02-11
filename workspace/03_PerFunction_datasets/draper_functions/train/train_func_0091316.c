gth_image_saver_jpeg_get_control (GthImageSaver *base)
{
	GthImageSaverJpeg  *self = GTH_IMAGE_SAVER_JPEG (base);
	char         **extensions;
	int            i;
	int            active_idx;

	_g_object_unref (self->priv->builder);
	self->priv->builder = _gtk_builder_new_from_file ("jpeg-options.ui", "cairo_io");

	active_idx = 0;
	extensions = g_strsplit (gth_image_saver_get_extensions (base), " ", -1);
	for (i = 0; extensions[i] != NULL; i++) {
		GtkTreeIter iter;

		gtk_list_store_append (GTK_LIST_STORE (gtk_builder_get_object (self->priv->builder, "jpeg_default_ext_liststore")), &iter);
		gtk_list_store_set (GTK_LIST_STORE (gtk_builder_get_object (self->priv->builder, "jpeg_default_ext_liststore")),
				    &iter,
				    0, extensions[i],
				    -1);
		if (g_str_equal (extensions[i], gth_image_saver_get_default_ext (base)))
			active_idx = i;
	}
	gtk_combo_box_set_active (GTK_COMBO_BOX (_gtk_builder_get_widget (self->priv->builder, "jpeg_default_extension_combobox")), active_idx);
	g_strfreev (extensions);

	gtk_adjustment_set_value (GTK_ADJUSTMENT (_gtk_builder_get_widget (self->priv->builder, "jpeg_quality_adjustment")),
				  g_settings_get_int (self->priv->settings, PREF_JPEG_QUALITY));
	gtk_adjustment_set_value (GTK_ADJUSTMENT (_gtk_builder_get_widget (self->priv->builder, "jpeg_smooth_adjustment")),
				  g_settings_get_int (self->priv->settings, PREF_JPEG_SMOOTHING));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (_gtk_builder_get_widget (self->priv->builder, "jpeg_optimize_checkbutton")),
				      g_settings_get_boolean (self->priv->settings, PREF_JPEG_OPTIMIZE));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (_gtk_builder_get_widget (self->priv->builder, "jpeg_progressive_checkbutton")),
				      g_settings_get_boolean (self->priv->settings, PREF_JPEG_PROGRESSIVE));

	return _gtk_builder_get_widget (self->priv->builder, "jpeg_options");
}
