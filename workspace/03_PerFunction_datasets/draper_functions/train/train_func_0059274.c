create_delegate_trampoline_data (MonoDomain *domain, MonoClass *klass, MonoMethod *method)
{
	DelegateTrampInfo *tramp_data;
	MonoMethod *invoke;
	MonoError err;


	invoke = mono_get_delegate_invoke (klass);
	g_assert (invoke);

	tramp_data = mono_domain_alloc (domain, sizeof (DelegateTrampInfo));
	tramp_data->invoke = invoke;
	tramp_data->impl_this = mono_arch_get_delegate_invoke_impl (mono_method_signature (invoke), TRUE);
	tramp_data->impl_nothis = mono_arch_get_delegate_invoke_impl (mono_method_signature (invoke), FALSE);
	tramp_data->method = method;
	if (method) {
		mono_error_init (&err);
		tramp_data->sig = mono_method_signature_checked (method, &err);
		tramp_data->need_rgctx_tramp = mono_method_needs_static_rgctx_invoke (method, FALSE);
	}

	return tramp_data;
}
