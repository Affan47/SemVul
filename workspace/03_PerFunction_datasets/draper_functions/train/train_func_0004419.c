ck_ht_init(struct ck_ht *table,
    unsigned int mode,
    ck_ht_hash_cb_t *h,
    struct ck_malloc *m,
    CK_HT_TYPE entries,
    uint64_t seed)
{

	if (m == NULL || m->malloc == NULL || m->free == NULL)
		return false;

	table->m = m;
	table->mode = mode;
	table->seed = seed;

	if (h == NULL) {
		table->h = ck_ht_hash_wrapper;
	} else {
		table->h = h;
	}

	table->map = ck_ht_map_create(table, entries);
	return table->map != NULL;
}
