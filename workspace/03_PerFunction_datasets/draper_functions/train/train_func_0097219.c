gkm_secret_module_dispose (GObject *obj)
{
	GkmSecretModule *self = GKM_SECRET_MODULE (obj);

	if (self->tracker)
		g_object_unref (self->tracker);
	self->tracker = NULL;

	if (self->session_credential)
		g_object_unref (self->session_credential);
	self->session_credential = NULL;

	g_hash_table_remove_all (self->collections);

	G_OBJECT_CLASS (gkm_secret_module_parent_class)->dispose (obj);
}
