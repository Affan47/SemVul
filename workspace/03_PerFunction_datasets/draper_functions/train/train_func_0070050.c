iso3166_close(void)
{
	size_t i;

	for (i = 0; i < G_N_ELEMENTS(iso3166_entries); i++) {
		iso3166_entry_t *entry = &iso3166_entries[i];
		atom_str_free_null(&entry->country);
	}
}
