zend_hash_graceful_destroy(HashTable *ht)
{
	Bucket *p;

	IS_CONSISTENT(ht);

	p = ht->pListHead;
	while (p != NULL) {
		p = zend_hash_apply_deleter(ht, p);
	}
	if (ht->nTableMask) {
		pefree(ht->arBuckets, ht->persistent);
	}

	SET_INCONSISTENT(HT_DESTROYED);
}
