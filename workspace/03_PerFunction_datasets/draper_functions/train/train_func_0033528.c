mono_emit_jit_map (MonoJitInfo *jinfo)
{
	if (perf_map_file) {
		char *name = mono_method_full_name (jinfo_get_method (jinfo), TRUE);
		mono_emit_jit_tramp (jinfo->code_start, jinfo->code_size, name);
		g_free (name);
	}
}
