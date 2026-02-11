_gth_slideshow_load_current_image (GthSlideshow *self)
{
	GthFileData *requested_file;
	GthFileData *next_file;
	GthFileData *prev_file;
	int          screen_width;
	int          screen_height;
	GdkScreen   *screen;

	if (self->priv->next_event != 0) {
		g_source_remove (self->priv->next_event);
		self->priv->next_event = 0;
	}

	if (self->priv->current == NULL) {
		if (! self->priv->one_loaded || ! self->priv->wrap_around) {
			_gth_slideshow_close (self);
			return;
		}
		_gth_slideshow_reset_current (self);
	}

	requested_file = (GthFileData *) self->priv->current->data;
	if (self->priv->current->next != NULL)
		next_file = (GthFileData *) self->priv->current->next->data;
	else
		next_file = NULL;
	if (self->priv->current->prev != NULL)
		prev_file = (GthFileData *) self->priv->current->prev->data;
	else
		prev_file = NULL;

	screen_width = -1;
	screen_height = -1;
	screen = gtk_widget_get_screen (GTK_WIDGET (self));
	if (screen != NULL) {
		screen_width = gdk_screen_get_width (screen);
		screen_height = gdk_screen_get_height (screen);
	}

	gth_image_preloader_load (self->priv->preloader,
				  requested_file,
				  MAX (screen_width, screen_height),
				  next_file,
				  prev_file,
				  NULL);
}
