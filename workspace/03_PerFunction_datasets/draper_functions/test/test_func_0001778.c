dom_property_exists(zval *object, zval *member, int check_empty TSRMLS_DC)
{
	dom_object *obj;
	zval tmp_member;
	dom_prop_handler *hnd;
	zend_object_handlers *std_hnd;
	int ret, retval=0;

 	if (member->type != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
	}

	ret = FAILURE;
	obj = (dom_object *)zend_objects_get_address(object TSRMLS_CC);

	if (obj->prop_handler != NULL) {
		ret = zend_hash_find((HashTable *)obj->prop_handler, Z_STRVAL_P(member), Z_STRLEN_P(member)+1, (void **) &hnd);
	}
	if (ret == SUCCESS) {
		zval *tmp;

		if (check_empty == 2) {
			retval = 1;
		} else if (hnd->read_func(obj, &tmp TSRMLS_CC) == SUCCESS) {
			Z_SET_REFCOUNT_P(tmp, 1);
			Z_UNSET_ISREF_P(tmp);
			if (check_empty == 1) {
				retval = zend_is_true(tmp);
			} else if (check_empty == 0) {
				retval = (Z_TYPE_P(tmp) != IS_NULL);
			}
			zval_ptr_dtor(&tmp);
		}
	} else {
		std_hnd = zend_get_std_object_handlers();
		retval = std_hnd->has_property(object, member, check_empty TSRMLS_CC);
	}

	if (member == &tmp_member) {
		zval_dtor(member);
	}
	return retval;
}
