create_simple_asyncresult (MonoObject *target, MonoObject *state)
{
	MonoDomain *domain = mono_domain_get ();
	MonoAsyncResult *ares;


	ares = (MonoAsyncResult *) mono_object_new (domain, mono_defaults.asyncresult_class);
	MONO_OBJECT_SETREF (ares, async_delegate, target);
	MONO_OBJECT_SETREF (ares, async_state, state);
	return ares;
}
