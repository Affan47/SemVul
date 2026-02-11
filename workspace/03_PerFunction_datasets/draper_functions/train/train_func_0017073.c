mono_arch_exceptions_init (void)
{
	GSList *tramps, *l;
	gpointer tramp;

	if (mono_aot_only) {
		throw_pending_exception = mono_aot_get_trampoline ("throw_pending_exception");
		tramp = mono_aot_get_trampoline ("llvm_throw_corlib_exception_trampoline");
		mono_register_jit_icall (tramp, "llvm_throw_corlib_exception_trampoline", NULL, TRUE);
		tramp = mono_aot_get_trampoline ("llvm_throw_corlib_exception_abs_trampoline");
		mono_register_jit_icall (tramp, "llvm_throw_corlib_exception_abs_trampoline", NULL, TRUE);
		tramp = mono_aot_get_trampoline ("llvm_resume_unwind_trampoline");
		mono_register_jit_icall (tramp, "llvm_resume_unwind_trampoline", NULL, TRUE);
	} else {

		throw_pending_exception = mono_arch_get_throw_pending_exception (NULL, FALSE);

		tramps = mono_amd64_get_exception_trampolines (FALSE);
		for (l = tramps; l; l = l->next) {
			MonoTrampInfo *info = l->data;

			mono_register_jit_icall (info->code, g_strdup (info->name), NULL, TRUE);
			mono_tramp_info_register (info);
		}
		g_slist_free (tramps);
	}
}
