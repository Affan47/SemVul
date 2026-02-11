mono_free_altstack (MonoJitTlsData *tls)
{
	stack_t sa;
	int err;

	sa.ss_sp = tls->signal_stack;
	sa.ss_size = MONO_ARCH_SIGNAL_STACK_SIZE;
	sa.ss_flags = SS_DISABLE;
	err = sigaltstack  (&sa, NULL);
	g_assert (err == 0);

	if (tls->signal_stack)
		mono_vfree (tls->signal_stack, MONO_ARCH_SIGNAL_STACK_SIZE);
	if (tls->stack_ovf_valloced)
		mono_vfree (tls->stack_ovf_guard_base, tls->stack_ovf_guard_size);
	else
		mono_mprotect (tls->stack_ovf_guard_base, tls->stack_ovf_guard_size, MONO_MMAP_READ|MONO_MMAP_WRITE);
}
