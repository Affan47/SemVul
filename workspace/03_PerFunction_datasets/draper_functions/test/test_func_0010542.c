mini_jit_info_table_find_ext (MonoDomain *domain, char *addr, gboolean allow_trampolines, MonoDomain **out_domain)
{
	MonoJitInfo *ji;
	MonoInternalThread *t = mono_thread_internal_current ();
	gpointer *refs;

	if (out_domain)
		*out_domain = NULL;

	ji = mono_jit_info_table_find_internal (domain, addr, TRUE, allow_trampolines);
	if (ji) {
		if (out_domain)
			*out_domain = domain;
		return ji;
	}


	if (domain != mono_get_root_domain ()) {
		ji = mono_jit_info_table_find_internal (mono_get_root_domain (), addr, TRUE, allow_trampolines);
		if (ji) {
			if (out_domain)
				*out_domain = mono_get_root_domain ();
			return ji;
		}
	}

	if (!t)
		return NULL;

	refs = (gpointer *)((t->appdomain_refs) ? *(gpointer *) t->appdomain_refs : NULL);
	for (; refs && *refs; refs++) {
		if (*refs != domain && *refs != mono_get_root_domain ()) {
			ji = mono_jit_info_table_find_internal ((MonoDomain*) *refs, addr, TRUE, allow_trampolines);
			if (ji) {
				if (out_domain)
					*out_domain = (MonoDomain*) *refs;
				return ji;
			}
		}
	}

	return NULL;
}
