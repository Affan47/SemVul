mono_jit_info_table_find_internal (MonoDomain *domain, char *addr, gboolean try_aot)
{
	MonoJitInfoTable *table;
	MonoJitInfo *ji, *module_ji;
	MonoThreadHazardPointers *hp = mono_hazard_pointer_get ();

	++mono_stats.jit_info_table_lookup_count;


	table = get_hazardous_pointer ((gpointer volatile*)&domain->jit_info_table, hp, JIT_INFO_TABLE_HAZARD_INDEX);

	ji = jit_info_table_find (table, hp, (gint8*)addr);
	if (hp)
		mono_hazard_pointer_clear (hp, JIT_INFO_TABLE_HAZARD_INDEX);
	if (ji)
		return ji;


	if (try_aot && mono_root_domain && mono_root_domain->aot_modules) {
		table = get_hazardous_pointer ((gpointer volatile*)&mono_root_domain->aot_modules, hp, JIT_INFO_TABLE_HAZARD_INDEX);
		module_ji = jit_info_table_find (table, hp, (gint8*)addr);
		if (module_ji)
			ji = jit_info_find_in_aot_func (domain, module_ji->d.image, addr);
		if (hp)
			mono_hazard_pointer_clear (hp, JIT_INFO_TABLE_HAZARD_INDEX);
	}

	return ji;
}
