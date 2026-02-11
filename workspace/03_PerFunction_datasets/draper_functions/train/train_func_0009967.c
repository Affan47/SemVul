create_jit_info_for_trampoline (MonoMethod *wrapper, MonoTrampInfo *info)
{
	MonoDomain *domain = mono_get_root_domain ();
	MonoJitInfo *jinfo;
	guint8 *uw_info;
	guint32 info_len;

	if (info->uw_info) {
		uw_info = info->uw_info;
		info_len = info->uw_info_len;
	} else {
		uw_info = mono_unwind_ops_encode (info->unwind_ops, &info_len);
	}

	jinfo = mono_domain_alloc0 (domain, MONO_SIZEOF_JIT_INFO);
	jinfo->d.method = wrapper;
	jinfo->code_start = info->code;
	jinfo->code_size = info->code_size;
	jinfo->used_regs = mono_cache_unwind_info (uw_info, info_len);

	if (!info->uw_info)
		g_free (uw_info);

	return jinfo;
}
