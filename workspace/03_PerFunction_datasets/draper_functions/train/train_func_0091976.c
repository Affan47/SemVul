is_a_impl(INTERNAL_FUNCTION_PARAMETERS, zend_bool only_subclass)
{
	zval *obj;
	char *class_name;
	int class_name_len;
	zend_class_entry *instance_ce;
	zend_class_entry **ce;
	zend_bool allow_string = only_subclass;
	zend_bool retval;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zs|b", &obj, &class_name, &class_name_len, &allow_string) == FAILURE) {
		return;
	}


	if (allow_string && Z_TYPE_P(obj) == IS_STRING) {
		zend_class_entry **the_ce;
		if (zend_lookup_class(Z_STRVAL_P(obj), Z_STRLEN_P(obj), &the_ce TSRMLS_CC) == FAILURE) {
			RETURN_FALSE;
		}
		instance_ce = *the_ce;
	} else if (Z_TYPE_P(obj) == IS_OBJECT && HAS_CLASS_ENTRY(*obj)) {
		instance_ce = Z_OBJCE_P(obj);
	} else {
		RETURN_FALSE;
	}

	if (zend_lookup_class_ex(class_name, class_name_len, NULL, 0, &ce TSRMLS_CC) == FAILURE) {
		retval = 0;
	} else {
		if (only_subclass && instance_ce == *ce) {
			retval = 0;
 		} else {
			retval = instanceof_function(instance_ce, *ce TSRMLS_CC);
		}
	}

	RETURN_BOOL(retval);
}
