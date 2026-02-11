mono_create_class_init_trampoline (MonoVTable *vtable)
{
	gpointer code, ptr;
	MonoDomain *domain = vtable->domain;

	g_assert (!vtable->klass->generic_container);


	mono_domain_lock (domain);
	ptr =
		g_hash_table_lookup (domain_jit_info (domain)->class_init_trampoline_hash,
								  vtable);
	mono_domain_unlock (domain);
	if (ptr)
		return ptr;

	code = mono_create_specific_trampoline (vtable, MONO_TRAMPOLINE_CLASS_INIT, domain, NULL);

	ptr = mono_create_ftnptr (domain, code);


	mono_domain_lock (domain);
	g_hash_table_insert (domain_jit_info (domain)->class_init_trampoline_hash,
							  vtable, ptr);
	mono_domain_unlock (domain);

	mono_trampolines_lock ();
	if (!class_init_hash_addr)
		class_init_hash_addr = g_hash_table_new (NULL, NULL);
	g_hash_table_insert (class_init_hash_addr, ptr, vtable);
	mono_trampolines_unlock ();

	return ptr;
}
