ck_ht_grow_spmc(struct ck_ht *table, CK_HT_TYPE capacity)
{
	struct ck_ht_map *map, *update;
	struct ck_ht_entry *bucket, *previous;
	struct ck_ht_hash h;
	size_t k, i, j, offset;
	CK_HT_TYPE probes;

restart:
	map = table->map;

	if (map->capacity >= capacity)
		return false;

	update = ck_ht_map_create(table, capacity);
	if (update == NULL)
		return false;

	for (k = 0; k < map->capacity; k++) {
		previous = &map->entries[k];

		if (previous->key == CK_HT_KEY_EMPTY || previous->key == CK_HT_KEY_TOMBSTONE)
			continue;

		if (table->mode & CK_HT_MODE_BYTESTRING) {
#ifdef CK_HT_PP
			void *key;
			uint16_t key_length;

			key = ck_ht_entry_key(previous);
			key_length = ck_ht_entry_key_length(previous);
#endif

#ifndef CK_HT_PP
			h.value = previous->hash;
#else
			table->h(&h, key, key_length, table->seed);
#endif
		} else {
#ifndef CK_HT_PP
			h.value = previous->hash;
#else
			table->h(&h, &previous->key, sizeof(previous->key), table->seed);
#endif
		}

		offset = h.value & update->mask;
		probes = 0;

		for (i = 0; i < update->probe_limit; i++) {
			bucket = (void *)((uintptr_t)(update->entries + offset) & ~(CK_MD_CACHELINE - 1));

			for (j = 0; j < CK_HT_BUCKET_LENGTH; j++) {
				struct ck_ht_entry *cursor = bucket + ((j + offset) & (CK_HT_BUCKET_LENGTH - 1));

				probes++;
				if (CK_CC_LIKELY(cursor->key == CK_HT_KEY_EMPTY)) {
					*cursor = *previous;
					update->n_entries++;
					ck_ht_map_bound_set(update, h, probes);
					break;
				}
			}

			if (j < CK_HT_BUCKET_LENGTH)
				break;

			offset = ck_ht_map_probe_next(update, offset, h, probes);
		}

		if (i == update->probe_limit) {


			ck_ht_map_destroy(table->m, update, false);
			capacity <<= 1;
			goto restart;
		}
	}

	ck_pr_fence_store();
	ck_pr_store_ptr_unsafe(&table->map, update);
	ck_ht_map_destroy(table->m, map, true);
	return true;
}
