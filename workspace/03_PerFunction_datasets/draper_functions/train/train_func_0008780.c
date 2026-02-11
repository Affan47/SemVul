compare_entries(tentry *eclean, tentry *enew)
{
	GPtrArray *mods = g_ptr_array_new();
	compare_ptr_arrays(entry_attributes(eclean),
			   entry_attributes(enew),
			   named_array_ptr_cmp,
			   (note_function) note_attributes,
			   mods);
	if (!mods->len) {
		g_ptr_array_free(mods, 1);
		return 0;
	}
	g_ptr_array_add(mods, 0);
	{
		LDAPMod **result = (LDAPMod **) mods->pdata;
		g_ptr_array_free(mods, 0);
		return result;
	}
}
