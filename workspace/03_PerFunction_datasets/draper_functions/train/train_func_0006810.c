_phpi_pop(INTERNAL_FUNCTION_PARAMETERS, int off_the_end)
{
	zval *stack,
		 **val;
	char *key = NULL;
	uint key_len = 0;
	ulong index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &stack) == FAILURE) {
		return;
	}

	if (zend_hash_num_elements(Z_ARRVAL_P(stack)) == 0) {
		return;
	}


	if (off_the_end) {
		zend_hash_internal_pointer_end(Z_ARRVAL_P(stack));
	} else {
		zend_hash_internal_pointer_reset(Z_ARRVAL_P(stack));
	}
	zend_hash_get_current_data(Z_ARRVAL_P(stack), (void **)&val);
	RETVAL_ZVAL(*val, 1, 0);


	zend_hash_get_current_key_ex(Z_ARRVAL_P(stack), &key, &key_len, &index, 0, NULL);
	if (key && Z_ARRVAL_P(stack) == &EG(symbol_table)) {
		zend_delete_global_variable(key, key_len - 1 TSRMLS_CC);
	} else {
		zend_hash_del_key_or_index(Z_ARRVAL_P(stack), key, key_len, index, (key) ? HASH_DEL_KEY : HASH_DEL_INDEX);
	}


	if (!off_the_end) {
		unsigned int k = 0;
		int should_rehash = 0;
		Bucket *p = Z_ARRVAL_P(stack)->pListHead;
		while (p != NULL) {
			if (p->nKeyLength == 0) {
				if (p->h != k) {
					p->h = k++;
					should_rehash = 1;
				} else {
					k++;
				}
			}
			p = p->pListNext;
		}
		Z_ARRVAL_P(stack)->nNextFreeElement = k;
		if (should_rehash) {
			zend_hash_rehash(Z_ARRVAL_P(stack));
		}
	} else if (!key_len && index >= Z_ARRVAL_P(stack)->nNextFreeElement - 1) {
		Z_ARRVAL_P(stack)->nNextFreeElement = Z_ARRVAL_P(stack)->nNextFreeElement - 1;
	}

	zend_hash_internal_pointer_reset(Z_ARRVAL_P(stack));
}
