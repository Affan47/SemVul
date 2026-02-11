nautilus_desktop_background_finalize (GObject *object)
{
	NautilusDesktopBackground *self;

	self = NAUTILUS_DESKTOP_BACKGROUND (object);

	g_signal_handlers_disconnect_by_func (gnome_background_preferences,
					      background_settings_change_event_cb,
					      self);

	free_background_surface (self);
	free_fade (self);

	g_clear_object (&self->details->bg);

	G_OBJECT_CLASS (nautilus_desktop_background_parent_class)->finalize (object);
}
