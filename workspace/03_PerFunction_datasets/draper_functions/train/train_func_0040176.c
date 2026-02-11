gcr_key_renderer_dispose (GObject *obj)
{
	GcrKeyRenderer *self = GCR_KEY_RENDERER (obj);

	if (self->pv->spk)
		g_bytes_unref (self->pv->spk);
	self->pv->spk = NULL;

	if (self->pv->object && self->pv->notify_sig) {
		g_signal_handler_disconnect (self->pv->object, self->pv->notify_sig);
		self->pv->notify_sig = 0;
	}
	g_clear_object (&self->pv->object);

	G_OBJECT_CLASS (gcr_key_renderer_parent_class)->dispose (obj);
}
