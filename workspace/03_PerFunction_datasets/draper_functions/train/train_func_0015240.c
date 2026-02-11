hash_table_destroy_real(hash_table_t *ht)
{
	hash_table_check(ht);
	ht_synchronize(ht);
	g_assert(!ht->once);

	hash_table_reset(ht);
	if (ht->thread_safe) {
		mutex_destroy(&ht->external_lock);
		mutex_destroy(&ht->lock);
	}
	ht->magic = 0;
	free(ht);
}
