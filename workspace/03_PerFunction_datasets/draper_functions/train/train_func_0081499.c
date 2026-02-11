mono_create_monitor_exit_trampoline (void)
{
	static gpointer code;

	if (mono_aot_only) {
		if (!code)
			code = mono_aot_get_trampoline ("monitor_exit_trampoline");
		return code;
	}

#ifdef MONO_ARCH_MONITOR_OBJECT_REG
	mono_trampolines_lock ();

	if (!code) {
		MonoTrampInfo *info;

		code = mono_arch_create_monitor_exit_trampoline (&info, FALSE);
		mono_tramp_info_register (info);
	}

	mono_trampolines_unlock ();
#else
	code = NULL;
	g_assert_not_reached ();
#endif
	return code;
}
