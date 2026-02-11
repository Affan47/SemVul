try_more_restore (void)
{
	MonoJitTlsData *jit_tls = (MonoJitTlsData *)mono_native_tls_get_value (mono_jit_tls_id);
	if (try_restore_stack_protection (jit_tls, 500))
		jit_tls->restore_stack_prot = NULL;
}
