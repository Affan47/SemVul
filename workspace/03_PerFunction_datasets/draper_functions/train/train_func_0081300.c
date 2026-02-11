mono_aot_get_imt_thunk (MonoVTable *vtable, MonoDomain *domain, MonoIMTCheckItem **imt_entries, int count, gpointer fail_tramp)
{
	guint32 got_offset;
	gpointer code;
	gpointer *buf;
	int i, index, real_count;
	MonoAotModule *amodule;

	real_count = 0;
	for (i = 0; i < count; ++i) {
		MonoIMTCheckItem *item = imt_entries [i];

		if (item->is_equals)
			real_count ++;
	}


	buf = mono_domain_alloc (domain, (real_count + 1) * 2 * sizeof (gpointer));
	index = 0;
	for (i = 0; i < count; ++i) {
		MonoIMTCheckItem *item = imt_entries [i];

		if (!item->is_equals)
			continue;

		g_assert (item->key);

		buf [(index * 2)] = item->key;
		if (item->has_target_code) {
			gpointer *p = mono_domain_alloc (domain, sizeof (gpointer));
			*p = item->value.target_code;
			buf [(index * 2) + 1] = p;
		} else {
			buf [(index * 2) + 1] = &(vtable->vtable [item->value.vtable_slot]);
		}
		index ++;
	}
	buf [(index * 2)] = NULL;
	buf [(index * 2) + 1] = fail_tramp;

	if (USE_PAGE_TRAMPOLINES) {
		code = get_new_imt_trampoline_from_page (buf);
	} else {
		code = get_numerous_trampoline (MONO_AOT_TRAMP_IMT_THUNK, 1, &amodule, &got_offset, NULL);

		amodule->got [got_offset] = buf;
	}

	return code;
}
