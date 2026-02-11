gck_object_get_async (GckObject *self,
                      const gulong *attr_types,
                      guint n_attr_types,
                      GCancellable *cancellable,
                      GAsyncReadyCallback callback,
                      gpointer user_data)
{
	GetAttributes *args;
	guint i;

	g_return_if_fail (GCK_IS_OBJECT (self));

	args = _gck_call_async_prep (self->pv->session, self, perform_get_attributes,
	                             NULL, sizeof (*args), free_get_attributes);

	gck_builder_init (&args->builder);
	for (i = 0; i < n_attr_types; ++i)
		gck_builder_add_empty (&args->builder, attr_types[i]);

	args->object = self->pv->handle;

	_gck_call_async_ready_go (args, cancellable, callback, user_data);
}
