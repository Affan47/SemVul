mono_aot_plt_resolve (gpointer aot_module, guint32 plt_info_offset, guint8 *code)
{
#ifdef MONO_ARCH_AOT_SUPPORTED
	guint8 *p, *target, *plt_entry;
	MonoJumpInfo ji;
	MonoAotModule *module = (MonoAotModule*)aot_module;
	gboolean res, no_ftnptr = FALSE;
	MonoMemPool *mp;
	gboolean using_gsharedvt = FALSE;


	p = &module->blob [plt_info_offset];

	ji.type = (MonoJumpInfoType)decode_value (p, &p);

	mp = mono_mempool_new ();
	res = decode_patch (module, mp, &ji, p, &p);

	if (!res) {
		mono_mempool_destroy (mp);
		return NULL;
	}

#ifdef MONO_ARCH_GSHAREDVT_SUPPORTED
	using_gsharedvt = TRUE;
#endif


	if (mono_aot_only && ji.type == MONO_PATCH_INFO_METHOD && !ji.data.method->is_generic && !mono_method_check_context_used (ji.data.method) && !(ji.data.method->iflags & METHOD_IMPL_ATTRIBUTE_SYNCHRONIZED) &&
		!mono_method_needs_static_rgctx_invoke (ji.data.method, FALSE) && !using_gsharedvt) {
		target = (guint8 *)mono_jit_compile_method (ji.data.method);
		no_ftnptr = TRUE;
	} else {
		target = (guint8 *)mono_resolve_patch_target (NULL, mono_domain_get (), NULL, &ji, TRUE);
	}


	if (ji.type == MONO_PATCH_INFO_ABS || ji.type == MONO_PATCH_INFO_INTERNAL_METHOD || ji.type == MONO_PATCH_INFO_ICALL_ADDR || ji.type == MONO_PATCH_INFO_JIT_ICALL_ADDR || ji.type == MONO_PATCH_INFO_RGCTX_FETCH) {

#ifdef PPC_USES_FUNCTION_DESCRIPTOR

		if (ji.type != MONO_PATCH_INFO_INTERNAL_METHOD && ji.type != MONO_PATCH_INFO_JIT_ICALL_ADDR && ji.type != MONO_PATCH_INFO_ICALL_ADDR)
			g_assert (((gpointer*)target) [2] == 0);
#endif

	} else if (!no_ftnptr) {
#ifdef PPC_USES_FUNCTION_DESCRIPTOR
		g_assert (((gpointer*)target) [2] != 0);
#endif
		target = (guint8 *)mono_create_ftnptr (mono_domain_get (), target);
	}

	mono_mempool_destroy (mp);


	plt_entry = mono_aot_get_plt_entry (code);
	g_assert (plt_entry);
	mono_aot_patch_plt_entry (code, plt_entry, module->got, NULL, target);

	return target;
#else
	g_assert_not_reached ();
	return NULL;
#endif
}
