gth_image_viewer_page_set_image (GthImageViewerPage *self,
			 	 cairo_surface_t    *image,
			 	 gboolean            add_to_history)
{
	if (gth_image_viewer_page_get_image (self) == image)
		return;

	if (add_to_history)
		gth_image_history_add_image (self->priv->history, image, TRUE);

	_gth_image_viewer_page_set_image (self, image, TRUE);
	self->priv->image_changed = TRUE;

	if (add_to_history)
		gth_viewer_page_focus (GTH_VIEWER_PAGE (self));
}
