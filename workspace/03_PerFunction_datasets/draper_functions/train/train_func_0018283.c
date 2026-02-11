gkm_manager_finalize (GObject *obj)
{
	GkmManager *self = GKM_MANAGER (obj);

	g_assert (!self->pv->objects);
	g_hash_table_destroy (self->pv->index_by_attribute);
	g_hash_table_destroy (self->pv->index_by_property);

	G_OBJECT_CLASS (gkm_manager_parent_class)->finalize (obj);
}
