gth_media_viewer_page_real_show (GthViewerPage *base)
{
	GthMediaViewerPage *self = GTH_MEDIA_VIEWER_PAGE (base);
	GError             *error = NULL;

	self->priv->visible = TRUE;

	if (self->priv->merge_id == 0) {
		self->priv->merge_id = gtk_ui_manager_add_ui_from_string (gth_browser_get_ui_manager (self->priv->browser), media_viewer_ui_info, -1, &error);
		if (self->priv->merge_id == 0) {
			g_warning ("ui building failed: %s", error->message);
			g_error_free (error);
		}
	}
	gth_viewer_page_focus (GTH_VIEWER_PAGE (self));

	create_playbin (self);
	if (self->priv->file_data != NULL) {
		char *uri;

		uri = g_file_get_uri (self->priv->file_data->file);
		_gth_media_viewer_page_set_uri (self, uri, GST_STATE_PLAYING);

		g_free (uri);
	}
}
