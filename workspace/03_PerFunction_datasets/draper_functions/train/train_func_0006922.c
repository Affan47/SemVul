zend_hash_quick_exists(const HashTable *ht, const char *arKey, uint nKeyLength, ulong h)
{
	uint nIndex;
	Bucket *p;

	if (nKeyLength==0) {
		return zend_hash_index_exists(ht, h);
	}

	IS_CONSISTENT(ht);

	nIndex = h & ht->nTableMask;

	p = ht->arBuckets[nIndex];
	while (p != NULL) {
		if (p->arKey == arKey ||
			((p->h == h) && (p->nKeyLength == nKeyLength) && !memcmp(p->arKey, arKey, nKeyLength))) {
				return 1;
		}
		p = p->pNext;
	}
	return 0;

}
