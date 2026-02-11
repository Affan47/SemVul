_zend_hash_index_update_or_next_insert(HashTable *ht, ulong h, void *pData, uint nDataSize, void **pDest, int flag ZEND_FILE_LINE_DC)
{
	uint nIndex;
	Bucket *p;

	IS_CONSISTENT(ht);

	if (flag & HASH_NEXT_INSERT) {
		h = ht->nNextFreeElement;
	}
	nIndex = h & ht->nTableMask;

	p = ht->arBuckets[nIndex];
	while (p != NULL) {
		if ((p->nKeyLength == 0) && (p->h == h)) {
			if (flag & HASH_NEXT_INSERT || flag & HASH_ADD) {
				return FAILURE;
			}
			HANDLE_BLOCK_INTERRUPTIONS();
#if ZEND_DEBUG
			if (p->pData == pData) {
				ZEND_PUTS("Fatal error in zend_hash_index_update: p->pData == pData\n");
				HANDLE_UNBLOCK_INTERRUPTIONS();
				return FAILURE;
			}
#endif
			if (ht->pDestructor) {
				ht->pDestructor(p->pData);
			}
			UPDATE_DATA(ht, p, pData, nDataSize);
			HANDLE_UNBLOCK_INTERRUPTIONS();
			if ((long)h >= (long)ht->nNextFreeElement) {
				ht->nNextFreeElement = h < LONG_MAX ? h + 1 : LONG_MAX;
			}
			if (pDest) {
				*pDest = p->pData;
			}
			return SUCCESS;
		}
		p = p->pNext;
	}
	p = (Bucket *) pemalloc_rel(sizeof(Bucket) - 1, ht->persistent);
	if (!p) {
		return FAILURE;
	}
	p->nKeyLength = 0;
	p->h = h;
	INIT_DATA(ht, p, pData, nDataSize);
	if (pDest) {
		*pDest = p->pData;
	}

	CONNECT_TO_BUCKET_DLLIST(p, ht->arBuckets[nIndex]);

	HANDLE_BLOCK_INTERRUPTIONS();
	ht->arBuckets[nIndex] = p;
	CONNECT_TO_GLOBAL_DLLIST(p, ht);
	HANDLE_UNBLOCK_INTERRUPTIONS();

	if ((long)h >= (long)ht->nNextFreeElement) {
		ht->nNextFreeElement = h < LONG_MAX ? h + 1 : LONG_MAX;
	}
	ht->nNumOfElements++;
	ZEND_HASH_IF_FULL_DO_RESIZE(ht);
	return SUCCESS;
}
