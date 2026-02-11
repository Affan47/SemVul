mono_rgctx_lazy_fetch_trampoline (mgreg_t *regs, guint8 *code, gpointer data, guint8 *tramp)
{
	static gboolean inited = FALSE;
	static int num_lookups = 0;
	guint32 slot = GPOINTER_TO_UINT (data);
	mgreg_t *r = (mgreg_t*)regs;
	gpointer arg = (gpointer)(gssize)r [MONO_ARCH_VTABLE_REG];
	guint32 index = MONO_RGCTX_SLOT_INDEX (slot);
	gboolean mrgctx = MONO_RGCTX_SLOT_IS_MRGCTX (slot);

	trampoline_calls ++;

	if (!inited) {
		mono_counters_register ("RGCTX unmanaged lookups", MONO_COUNTER_GENERICS | MONO_COUNTER_INT, &num_lookups);
		inited = TRUE;
	}

	num_lookups++;

	if (mrgctx)
		return mono_method_fill_runtime_generic_context ((MonoMethodRuntimeGenericContext *)arg, index);
	else
		return mono_class_fill_runtime_generic_context ((MonoVTable *)arg, index);
}
