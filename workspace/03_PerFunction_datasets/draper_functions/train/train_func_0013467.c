print_flat_hash(HashTable *ht TSRMLS_DC)
{
	zval **tmp;
	char *string_key;
	HashPosition iterator;
	ulong num_key;
	uint str_len;
	int i = 0;

	zend_hash_internal_pointer_reset_ex(ht, &iterator);
	while (zend_hash_get_current_data_ex(ht, (void **) &tmp, &iterator) == SUCCESS) {
		if (i++ > 0) {
			ZEND_PUTS(",");
		}
		ZEND_PUTS("[");
		switch (zend_hash_get_current_key_ex(ht, &string_key, &str_len, &num_key, 0, &iterator)) {
			case HASH_KEY_IS_STRING:
				ZEND_PUTS(string_key);
				break;
			case HASH_KEY_IS_LONG:
				zend_printf("%ld", num_key);
				break;
		}
		ZEND_PUTS("] => ");
		zend_print_flat_zval_r(*tmp TSRMLS_CC);
		zend_hash_move_forward_ex(ht, &iterator);
	}
}
