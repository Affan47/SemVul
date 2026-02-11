_reflection_param_get_default_param(INTERNAL_FUNCTION_PARAMETERS)
{
	reflection_object *intern;
	parameter_reference *param;

	intern = (reflection_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	if (intern == NULL || intern->ptr == NULL) {
		if (EG(exception) && Z_OBJCE_P(EG(exception)) == reflection_exception_ptr) {
			return NULL;
		}
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Internal error: Failed to retrieve the reflection object");
	}

	param = intern->ptr;
	if (param->fptr->type != ZEND_USER_FUNCTION) {
		zend_throw_exception_ex(reflection_exception_ptr, 0 TSRMLS_CC, "Cannot determine default value for internal functions");
		return NULL;
	}

	return param;
}
