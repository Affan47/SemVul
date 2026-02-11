zend_user_serialize(zval *object, unsigned char **buffer, zend_uint *buf_len, zend_serialize_data *data TSRMLS_DC)
{
	zend_class_entry * ce = Z_OBJCE_P(object);
	zval *retval;
	int result;

	zend_call_method_with_0_params(&object, ce, &ce->serialize_func, "serialize", &retval);


	if (!retval || EG(exception)) {
		result = FAILURE;
	} else {
		switch(Z_TYPE_P(retval)) {
		case IS_NULL:

			zval_ptr_dtor(&retval);
			return FAILURE;
		case IS_STRING:
			*buffer = (unsigned char*)estrndup(Z_STRVAL_P(retval), Z_STRLEN_P(retval));
			*buf_len = Z_STRLEN_P(retval);
			result = SUCCESS;
			break;
		default:
			result = FAILURE;
			break;
		}
		zval_ptr_dtor(&retval);
	}

	if (result == FAILURE && !EG(exception)) {
		zend_throw_exception_ex(NULL, 0 TSRMLS_CC, "%s::serialize() must return a string or NULL", ce->name);
	}
	return result;
}
