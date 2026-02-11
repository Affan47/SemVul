zend_std_has_property(zval *object, zval *member, int has_set_exists TSRMLS_DC)
{
	zend_object *zobj;
	int result;
	zval **value;
	zval *tmp_member = NULL;
	zend_property_info *property_info;

	zobj = Z_OBJ_P(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		ALLOC_ZVAL(tmp_member);
		*tmp_member = *member;
		INIT_PZVAL(tmp_member);
		zval_copy_ctor(tmp_member);
		convert_to_string(tmp_member);
		member = tmp_member;
	}

#if DEBUG_OBJECT_HANDLERS
	fprintf(stderr, "Read object #%d property: %s\n", Z_OBJ_HANDLE_P(object), Z_STRVAL_P(member));
#endif

	property_info = zend_get_property_info(zobj->ce, member, 1 TSRMLS_CC);

	if (!property_info || zend_hash_quick_find(zobj->properties, property_info->name, property_info->name_length+1, property_info->h, (void **) &value) == FAILURE) {
		zend_guard *guard;

		result = 0;
		if ((has_set_exists != 2) &&
		    zobj->ce->__isset &&
		    zend_get_property_guard(zobj, property_info, member, &guard) == SUCCESS &&
		    !guard->in_isset) {
			zval *rv;


			Z_ADDREF_P(object);
			guard->in_isset = 1;
			rv = zend_std_call_issetter(object, member TSRMLS_CC);
			if (rv) {
				result = zend_is_true(rv);
				zval_ptr_dtor(&rv);
				if (has_set_exists && result) {
					if (!EG(exception) && zobj->ce->__get && !guard->in_get) {
						guard->in_get = 1;
						rv = zend_std_call_getter(object, member TSRMLS_CC);
						guard->in_get = 0;
						if (rv) {
							Z_ADDREF_P(rv);
							result = i_zend_is_true(rv);
							zval_ptr_dtor(&rv);
						} else {
							result = 0;
						}
					} else {
						result = 0;
					}
				}
			}
			guard->in_isset = 0;
			zval_ptr_dtor(&object);
		}
	} else {
		switch (has_set_exists) {
		case 0:
			result = (Z_TYPE_PP(value) != IS_NULL);
			break;
		default:
			result = zend_is_true(*value);
			break;
		case 2:
			result = 1;
			break;
		}
	}

	if (tmp_member) {
		zval_ptr_dtor(&tmp_member);
	}
	return result;
}
