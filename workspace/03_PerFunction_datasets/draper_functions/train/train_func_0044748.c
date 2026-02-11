_zend_hash_init(HashTable *ht, uint nSize, hash_func_t pHashFunction, dtor_func_t pDestructor, zend_bool persistent ZEND_FILE_LINE_DC)
{
	uint i = 3;
	Bucket **tmp;

	SET_INCONSISTENT(HT_OK);

	if (nSize >= 0x80000000) {

		ht->nTableSize = 0x80000000;
	} else {
		while ((1U << i) < nSize) {
			i++;
		}
		ht->nTableSize = 1 << i;
	}

	ht->nTableMask = ht->nTableSize - 1;
	ht->pDestructor = pDestructor;
	ht->arBuckets = NULL;
	ht->pListHead = NULL;
	ht->pListTail = NULL;
	ht->nNumOfElements = 0;
	ht->nNextFreeElement = 0;
	ht->pInternalPointer = NULL;
	ht->persistent = persistent;
	ht->nApplyCount = 0;
	ht->bApplyProtection = 1;


	if (persistent) {
		tmp = (Bucket **) calloc(ht->nTableSize, sizeof(Bucket *));
		if (!tmp) {
			return FAILURE;
		}
		ht->arBuckets = tmp;
	} else {
		tmp = (Bucket **) ecalloc_rel(ht->nTableSize, sizeof(Bucket *));
		if (tmp) {
			ht->arBuckets = tmp;
		}
	}

	return SUCCESS;
}
