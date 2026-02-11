mini_add_method_trampoline (MonoMethod *m, gpointer compiled_method, gboolean add_static_rgctx_tramp, gboolean add_unbox_tramp)
{
	gpointer addr = compiled_method;
	gboolean callee_gsharedvt, callee_array_helper;
	MonoMethod *jmethod = NULL;
	MonoJitInfo *ji;


	ji = mini_jit_info_table_find (mono_domain_get (), (char *)mono_get_addr_from_ftnptr (compiled_method), NULL);
	callee_gsharedvt = mini_jit_info_is_gsharedvt (ji);

	callee_array_helper = FALSE;
	if (m->wrapper_type == MONO_WRAPPER_MANAGED_TO_MANAGED) {
		WrapperInfo *info = mono_marshal_get_wrapper_info (m);


		if (info && info->subtype == WRAPPER_SUBTYPE_GENERIC_ARRAY_HELPER) {
			callee_array_helper = TRUE;
			m = info->d.generic_array_helper.method;
		}
	} else if (m->wrapper_type == MONO_WRAPPER_UNKNOWN) {
		WrapperInfo *info = mono_marshal_get_wrapper_info (m);


		if (info && info->subtype == WRAPPER_SUBTYPE_SYNCHRONIZED_INNER) {
			m = info->d.synchronized_inner.method;
		}
	}

	if (callee_gsharedvt)
		g_assert (m->is_inflated);

	addr = compiled_method;

	if (add_unbox_tramp) {


		if (mono_aot_only) {
			addr = mono_aot_get_unbox_trampoline (m);
		} else {
			unbox_trampolines ++;
			addr = mono_arch_get_unbox_trampoline (m, addr);
		}
	}

	if (ji && !ji->is_trampoline)
		jmethod = jinfo_get_method (ji);
	if (callee_gsharedvt && mini_is_gsharedvt_variable_signature (mono_method_signature (jmethod))) {
		MonoMethodSignature *sig, *gsig;


		sig = mono_method_signature (m);
		gsig = mono_method_signature (jmethod);

		addr = mini_get_gsharedvt_wrapper (TRUE, addr, sig, gsig, -1, FALSE);


	}

	if (callee_array_helper) {
		add_static_rgctx_tramp = FALSE;

		if (ji && (ji->from_aot || mono_aot_only)) {

			if (!mono_llvm_only && mono_method_needs_static_rgctx_invoke (jinfo_get_method (ji), TRUE))
				add_static_rgctx_tramp = TRUE;
		}
	}

	if (mono_llvm_only)
		add_static_rgctx_tramp = FALSE;

	if (add_static_rgctx_tramp)
		addr = mono_create_static_rgctx_trampoline (m, addr);

	return addr;
}
