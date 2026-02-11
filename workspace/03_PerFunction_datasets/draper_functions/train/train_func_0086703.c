php_array_walk(HashTable *target_hash, zval *userdata, int recursive TSRMLS_DC)
{
	zval **args[3],
		  *retval_ptr,
		  *key=NULL;
	char  *string_key;
	uint   string_key_len;
	ulong  num_key;


	args[1] = &key;
	args[2] = &userdata;
	if (userdata) {
		Z_ADDREF_P(userdata);
	}

	BG(array_walk_fci).retval_ptr_ptr = &retval_ptr;
	BG(array_walk_fci).param_count = userdata ? 3 : 2;
	BG(array_walk_fci).params = args;
	BG(array_walk_fci).no_separation = 0;


	zend_hash_internal_pointer_reset(target_hash);
	while (!EG(exception) && zend_hash_get_current_data(target_hash, (void **)&args[0]) == SUCCESS) {
		if (recursive && Z_TYPE_PP(args[0]) == IS_ARRAY) {
			HashTable *thash;
			zend_fcall_info orig_array_walk_fci;
			zend_fcall_info_cache orig_array_walk_fci_cache;

			SEPARATE_ZVAL_IF_NOT_REF(args[0]);
			thash = Z_ARRVAL_PP(args[0]);
			if (thash->nApplyCount > 1) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "recursion detected");
				if (userdata) {
					zval_ptr_dtor(&userdata);
				}
				return 0;
			}


			orig_array_walk_fci = BG(array_walk_fci);
			orig_array_walk_fci_cache = BG(array_walk_fci_cache);

			thash->nApplyCount++;
			php_array_walk(thash, userdata, recursive TSRMLS_CC);
			thash->nApplyCount--;


			BG(array_walk_fci) = orig_array_walk_fci;
			BG(array_walk_fci_cache) = orig_array_walk_fci_cache;
		} else {

			MAKE_STD_ZVAL(key);


			switch (zend_hash_get_current_key_ex(target_hash, &string_key, &string_key_len, &num_key, 0, NULL)) {
				case HASH_KEY_IS_LONG:
					Z_TYPE_P(key) = IS_LONG;
					Z_LVAL_P(key) = num_key;
					break;
				case HASH_KEY_IS_STRING:
					ZVAL_STRINGL(key, string_key, string_key_len - 1, 1);
					break;
			}


			if (zend_call_function(&BG(array_walk_fci), &BG(array_walk_fci_cache) TSRMLS_CC) == SUCCESS) {
				if (retval_ptr) {
					zval_ptr_dtor(&retval_ptr);
				}
			} else {
				if (key) {
					zval_ptr_dtor(&key);
					key = NULL;
				}
				break;
			}
		}

		if (key) {
			zval_ptr_dtor(&key);
			key = NULL;
		}
		zend_hash_move_forward(target_hash);
	}

	if (userdata) {
		zval_ptr_dtor(&userdata);
	}
	return 0;
}
