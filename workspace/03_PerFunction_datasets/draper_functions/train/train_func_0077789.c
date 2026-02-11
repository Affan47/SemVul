gcr_system_prompter_finalize (GObject *obj)
{
	GcrSystemPrompter *self = GCR_SYSTEM_PROMPTER (obj);

	_gcr_debug ("finalizing prompter");

	g_assert (self->pv->connection == NULL);
	g_assert (self->pv->prompter_registered == 0);

	g_hash_table_destroy (self->pv->callbacks);
	g_hash_table_destroy (self->pv->active);

	G_OBJECT_CLASS (gcr_system_prompter_parent_class)->finalize (obj);
}
