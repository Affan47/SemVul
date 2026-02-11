free_fade (NautilusDesktopBackground *self)
{
	if (self->details->fade != NULL) {
		g_object_unref (self->details->fade);
		self->details->fade = NULL;
	}
}
