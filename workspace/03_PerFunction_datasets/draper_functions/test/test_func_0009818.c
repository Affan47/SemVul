invalidate_frames (DebuggerTlsData *tls)
{
	int i;

	if (!tls)
		tls = mono_native_tls_get_value (debugger_tls_id);
	g_assert (tls);

	for (i = 0; i < tls->frame_count; ++i) {
		if (tls->frames [i]->jit)
			mono_debug_free_method_jit_info (tls->frames [i]->jit);
		g_free (tls->frames [i]);
	}
	g_free (tls->frames);
	tls->frame_count = 0;
	tls->frames = NULL;
}
