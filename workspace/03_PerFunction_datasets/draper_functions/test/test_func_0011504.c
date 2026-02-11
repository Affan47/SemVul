gth_image_viewer_page_real_deactivate (GthViewerPage *base)
{
	GthImageViewerPage *self;

	self = (GthImageViewerPage*) base;

	if (self->priv->browser_merge_id != 0) {
		gtk_ui_manager_remove_ui (gth_browser_get_ui_manager (self->priv->browser), self->priv->browser_merge_id);
		self->priv->browser_merge_id = 0;
	}

	gtk_ui_manager_remove_action_group (gth_browser_get_ui_manager (self->priv->browser), self->priv->actions);
	g_object_unref (self->priv->actions);
	self->priv->actions = NULL;

	g_signal_handler_disconnect (self->priv->preloader, self->priv->requested_ready_id);
	g_signal_handler_disconnect (self->priv->preloader, self->priv->original_size_ready_id);
	self->priv->requested_ready_id = 0;
	self->priv->original_size_ready_id = 0;

	g_object_unref (self->priv->preloader);
	self->priv->preloader = NULL;

	gth_browser_set_viewer_widget (self->priv->browser, NULL);
}
