mono_method_lookup_or_register_info (MonoMethod *method, gboolean in_mrgctx, gpointer data,
	MonoRgctxInfoType info_type, MonoGenericContext *generic_context)
{
	MonoClass *klass = method->klass;
	int type_argc, index;

	if (in_mrgctx) {
		MonoGenericInst *method_inst = mono_method_get_context (method)->method_inst;

		g_assert (method->is_inflated && method_inst);
		type_argc = method_inst->type_argc;
		g_assert (type_argc > 0);
	} else {
		type_argc = 0;
	}

	index = lookup_or_register_info (klass, type_argc, data, info_type, generic_context);


	if (in_mrgctx)
		return MONO_RGCTX_SLOT_MAKE_MRGCTX (index);
	else
		return MONO_RGCTX_SLOT_MAKE_RGCTX (index);
}
