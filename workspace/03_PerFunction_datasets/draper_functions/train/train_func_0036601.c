mono_runtime_free_method (MonoDomain *domain, MonoMethod *method)
{
	if (default_mono_free_method != NULL)
		default_mono_free_method (domain, method);

	mono_method_clear_object (domain, method);

	mono_free_method (method);
}
