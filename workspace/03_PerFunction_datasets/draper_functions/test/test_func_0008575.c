mini_jit_info_is_gsharedvt (MonoJitInfo *ji)
{
	if (ji && ji->has_generic_jit_info && (mono_jit_info_get_generic_sharing_context (ji)->var_is_vt ||
										   mono_jit_info_get_generic_sharing_context (ji)->mvar_is_vt))
		return TRUE;
	else
		return FALSE;
}
