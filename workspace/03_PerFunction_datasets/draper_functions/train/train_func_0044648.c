mono_mark_vreg_as_ref (MonoCompile *cfg, int vreg)
{
	if (vreg >= cfg->vreg_is_ref_len) {
		gboolean *tmp = cfg->vreg_is_ref;
		int size = cfg->vreg_is_ref_len;

		while (vreg >= cfg->vreg_is_ref_len)
			cfg->vreg_is_ref_len = cfg->vreg_is_ref_len ? cfg->vreg_is_ref_len * 2 : 32;
		cfg->vreg_is_ref = mono_mempool_alloc0 (cfg->mempool, sizeof (gboolean) * cfg->vreg_is_ref_len);
		if (size)
			memcpy (cfg->vreg_is_ref, tmp, size * sizeof (gboolean));
	}
	cfg->vreg_is_ref [vreg] = TRUE;
}
