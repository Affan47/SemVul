remove_object (GkmManager *self, GkmObject *object)
{
	CK_OBJECT_HANDLE handle;

	g_assert (GKM_IS_MANAGER (self));
	g_assert (GKM_IS_OBJECT (object));
	g_assert (gkm_object_get_manager (object) == self);

	handle = gkm_object_get_handle (object);
	g_assert (handle);


	g_signal_handlers_disconnect_by_func (object, G_CALLBACK (notify_attribute), self);
	g_signal_handlers_disconnect_by_func (object, G_CALLBACK (notify_property), self);
	g_hash_table_foreach (self->pv->index_by_attribute, index_remove_each, object);
	g_hash_table_foreach (self->pv->index_by_property, index_remove_each, object);


	self->pv->objects = g_list_remove (self->pv->objects, object);


	g_signal_emit (self, signals[OBJECT_REMOVED], 0, object);
}
