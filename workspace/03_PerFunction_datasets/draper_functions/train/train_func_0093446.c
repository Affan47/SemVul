zend_hash_apply_with_arguments(HashTable *ht TSRMLS_DC, apply_func_args_t apply_func, int num_args, ...)
{
	Bucket *p;
	va_list args;
	zend_hash_key hash_key;

	IS_CONSISTENT(ht);

	HASH_PROTECT_RECURSION(ht);

	p = ht->pListHead;
	while (p != NULL) {
		int result;
		va_start(args, num_args);
		hash_key.arKey = p->arKey;
		hash_key.nKeyLength = p->nKeyLength;
		hash_key.h = p->h;
		result = apply_func(p->pData TSRMLS_CC, num_args, args, &hash_key);

		if (result & ZEND_HASH_APPLY_REMOVE) {
			p = zend_hash_apply_deleter(ht, p);
		} else {
			p = p->pListNext;
		}
		if (result & ZEND_HASH_APPLY_STOP) {
			break;
		}
		va_end(args);
	}

	HASH_UNPROTECT_RECURSION(ht);
}
