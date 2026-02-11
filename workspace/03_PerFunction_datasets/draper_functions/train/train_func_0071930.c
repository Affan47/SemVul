gth_image_viewer_set_fit_mode__key_binding (GthImageViewer *self,
					    GthFit          fit_mode)
{
	if (self->priv->enable_zoom_with_keys)
		gth_image_viewer_set_fit_mode (self, fit_mode);
}
