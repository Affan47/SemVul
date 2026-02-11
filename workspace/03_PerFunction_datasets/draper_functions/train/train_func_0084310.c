apply_cb (gpointer user_data)
{
	GthFileToolAdjustColors *self = user_data;
	GtkWidget               *window;
	AdjustData              *adjust_data;

	if (self->priv->apply_event != 0) {
		g_source_remove (self->priv->apply_event);
		self->priv->apply_event = 0;
	}

	if (self->priv->image_task != NULL) {
		gth_task_cancel (self->priv->image_task);
		return FALSE;
	}

	window = gth_file_tool_get_window (GTH_FILE_TOOL (self));

	adjust_data = g_new0 (AdjustData, 1);
	adjust_data->self = self;
	adjust_data->viewer_page = g_object_ref (gth_browser_get_viewer_page (GTH_BROWSER (window)));
	adjust_data->source = cairo_surface_reference (self->priv->apply_to_original ? self->priv->source : self->priv->preview);
	adjust_data->gamma = pow (10, - (gtk_adjustment_get_value (self->priv->gamma_adj) / 100.0));
	adjust_data->brightness = gtk_adjustment_get_value (self->priv->brightness_adj) / 100.0 * -1.0;
	adjust_data->contrast = gtk_adjustment_get_value (self->priv->contrast_adj) / 100.0 * -1.0;
	adjust_data->saturation = gtk_adjustment_get_value (self->priv->saturation_adj) / 100.0 * -1.0;
	adjust_data->color_level[0] = gtk_adjustment_get_value (self->priv->cyan_red_adj);
	adjust_data->color_level[1] = gtk_adjustment_get_value (self->priv->magenta_green_adj);
	adjust_data->color_level[2] = gtk_adjustment_get_value (self->priv->yellow_blue_adj);

	self->priv->image_task = gth_image_task_new (_("Applying changes"),
						     adjust_colors_before,
						     adjust_colors_exec,
						     NULL,
						     adjust_data,
						     adjust_data_free);
	g_signal_connect (self->priv->image_task,
			  "completed",
			  G_CALLBACK (image_task_completed_cb),
			  self);
	gth_browser_exec_task (GTH_BROWSER (window), self->priv->image_task, FALSE);

	return FALSE;
}
