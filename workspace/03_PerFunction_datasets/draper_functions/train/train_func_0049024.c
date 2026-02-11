gck_session_finalize (GObject *obj)
{
	GckSession *self = GCK_SESSION (obj);

	g_assert (self->pv->handle == 0 || self->pv->discarded);

	g_clear_object (&self->pv->interaction);
	g_clear_object (&self->pv->slot);

	g_mutex_clear (self->pv->mutex);
	g_free (self->pv->mutex);

	G_OBJECT_CLASS (gck_session_parent_class)->finalize (obj);
}
