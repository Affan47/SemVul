gth_slideshow_finalize (GObject *object)
{
	GthSlideshow *self = GTH_SLIDESHOW (object);

	if (self->priv->next_event != 0)
		g_source_remove (self->priv->next_event);
	if (self->priv->hide_cursor_event != 0)
		g_source_remove (self->priv->hide_cursor_event);

	_g_object_unref (self->priv->pause_pixbuf);
	_g_object_unref (self->priv->current_pixbuf);
	_g_object_list_unref (self->priv->file_list);
	_g_object_unref (self->priv->browser);
	_g_object_unref (self->priv->preloader);
	_g_object_list_unref (self->priv->transitions);
	g_rand_free (self->priv->rand);
	g_strfreev (self->priv->audio_files);

#if HAVE_GSTREAMER
	if (self->priv->playbin != NULL) {
		gst_element_set_state (self->priv->playbin, GST_STATE_NULL);
		gst_object_unref (GST_OBJECT (self->priv->playbin));
		self->priv->playbin = NULL;
	}
#endif

	if (self->priv->screensaver != NULL) {
		gth_screensaver_uninhibit (self->priv->screensaver);
		g_object_unref (self->priv->screensaver);
	}

	G_OBJECT_CLASS (gth_slideshow_parent_class)->finalize (object);
}
