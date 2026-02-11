gth_image_viewer_page_real_show (GthViewerPage *base)
{
	GthImageViewerPage *self;
	GError             *error = NULL;

	self = (GthImageViewerPage*) base;

	if (self->priv->viewer_merge_id != 0)
		return;

	self->priv->viewer_merge_id = gtk_ui_manager_add_ui_from_string (gth_browser_get_ui_manager (self->priv->browser), image_viewer_ui_info, -1, &error);
	if (self->priv->viewer_merge_id == 0) {
		g_warning ("ui building failed: %s", error->message);
		g_error_free (error);
	}

	gth_viewer_page_focus (GTH_VIEWER_PAGE (self));
}
