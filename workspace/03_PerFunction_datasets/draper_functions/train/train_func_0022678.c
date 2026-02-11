restore_stack_protection (void)
{
	MonoJitTlsData *jit_tls = mono_native_tls_get_value (mono_jit_tls_id);
	MonoException *ex = mono_domain_get ()->stack_overflow_ex;


	if (try_restore_stack_protection (jit_tls, 4096))
		jit_tls->restore_stack_prot = NULL;
	else
		jit_tls->restore_stack_prot = try_more_restore_tramp;

	ex->trace_ips = NULL;
	ex->stack_trace = NULL;
	mono_raise_exception (ex);
}
