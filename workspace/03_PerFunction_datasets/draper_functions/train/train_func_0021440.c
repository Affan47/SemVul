gck_object_get_data_full (GckObject *self, gulong attr_type, GckAllocator allocator,
                           GCancellable *cancellable, gsize *n_data, GError **error)
{
	GetAttributeData args;
	gboolean ret;

	g_return_val_if_fail (GCK_IS_OBJECT (self), NULL);
	g_return_val_if_fail (n_data, NULL);
	g_return_val_if_fail (!error || !*error, NULL);

	if (!allocator)
		allocator = g_realloc;

	memset (&args, 0, sizeof (args));
	args.allocator = allocator;
	args.object = self->pv->handle;
	args.type = attr_type;

	ret = _gck_call_sync (self->pv->session, perform_get_attribute_data, NULL, &args, cancellable, error);


	if (!ret) {
		if (args.result)
			(allocator) (args.result, 0);
		return NULL;
	}

	*n_data = args.n_result;
	return args.result;
}
