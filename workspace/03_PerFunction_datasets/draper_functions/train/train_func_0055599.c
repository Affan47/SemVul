htable_val(const struct htable *ht,
			struct htable_iter *i, size_t hash, uintptr_t perfect)
{
	uintptr_t h2 = get_hash_ptr_bits(ht, hash) | perfect;

	while (ht->table[i->off]) {
		if (ht->table[i->off] != HTABLE_DELETED) {
			if (get_extra_ptr_bits(ht, ht->table[i->off]) == h2)
				return get_raw_ptr(ht, ht->table[i->off]);
		}
		i->off = (i->off + 1) & ((1 << ht->bits)-1);
		h2 &= ~perfect;
	}
	return NULL;
}
