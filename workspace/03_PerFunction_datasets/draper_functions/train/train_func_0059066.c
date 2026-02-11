mono_aot_get_method_from_token (MonoDomain *domain, MonoImage *image, guint32 token)
{
	MonoAotModule *aot_module = image->aot_module;
	int method_index;

	if (!aot_module)
		return NULL;

	method_index = mono_metadata_token_index (token) - 1;

	return load_method (domain, aot_module, image, NULL, token, method_index);
}
