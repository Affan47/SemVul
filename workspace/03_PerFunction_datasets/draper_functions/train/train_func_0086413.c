mono_image_register_token (MonoDynamicImage *assembly, guint32 token, MonoObject *obj)
{
	MonoObject *prev;

	dynamic_image_lock (assembly);
	prev = (MonoObject *)mono_g_hash_table_lookup (assembly->tokens, GUINT_TO_POINTER (token));
	if (prev) {


	} else {
		mono_g_hash_table_insert (assembly->tokens, GUINT_TO_POINTER (token), obj);
	}
	dynamic_image_unlock (assembly);
}
