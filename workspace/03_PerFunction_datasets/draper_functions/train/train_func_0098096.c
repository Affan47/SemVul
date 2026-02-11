gth_media_viewer_page_finalize (GObject *obj)
{
	GthMediaViewerPage *self;

	self = GTH_MEDIA_VIEWER_PAGE (obj);

        if (self->priv->update_progress_id != 0) {
                g_source_remove (self->priv->update_progress_id);
                self->priv->update_progress_id = 0;
        }

        if (self->priv->update_volume_id != 0) {
                g_source_remove (self->priv->update_volume_id);
                self->priv->update_volume_id = 0;
        }

	if (self->priv->playbin != NULL) {
		save_volume (self);
		gst_element_set_state (self->priv->playbin, GST_STATE_NULL);
		gst_object_unref (GST_OBJECT (self->priv->playbin));
		self->priv->playbin = NULL;
	}
	_g_object_unref (self->priv->icon);
	_g_object_unref (self->priv->file_data);
	if (self->priv->screensaver != NULL) {
		gth_screensaver_uninhibit (self->priv->screensaver);
		g_object_unref (self->priv->screensaver);
	}

	G_OBJECT_CLASS (gth_media_viewer_page_parent_class)->finalize (obj);
}
