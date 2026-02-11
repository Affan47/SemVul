mono_class_fill_runtime_generic_context (MonoVTable *class_vtable, guint8 *caller, guint32 slot)
{
	static gboolean inited = FALSE;
	static int num_alloced = 0;

	MonoDomain *domain = class_vtable->domain;
	MonoRuntimeGenericContext *rgctx;
	gpointer info;

	mono_domain_lock (domain);

	if (!inited) {
		mono_counters_register ("RGCTX num alloced", MONO_COUNTER_GENERICS | MONO_COUNTER_INT, &num_alloced);
		inited = TRUE;
	}

	rgctx = class_vtable->runtime_generic_context;
	if (!rgctx) {
		rgctx = alloc_rgctx_array (domain, 0, FALSE);
		class_vtable->runtime_generic_context = rgctx;
		num_alloced++;
	}

	mono_domain_unlock (domain);

	info = fill_runtime_generic_context (class_vtable, rgctx, caller, slot, 0);

	DEBUG (printf ("get rgctx slot: %s %d -> %p\n", mono_type_full_name (&class_vtable->klass->byval_arg), slot, info));

	return info;
}
