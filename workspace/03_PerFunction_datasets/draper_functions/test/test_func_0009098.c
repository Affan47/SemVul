php_output_start_user(zval *output_handler, size_t chunk_size, int flags TSRMLS_DC)
{
	php_output_handler *handler;

	if (output_handler) {
		handler = php_output_handler_create_user(output_handler, chunk_size, flags TSRMLS_CC);
	} else {
		handler = php_output_handler_create_internal(ZEND_STRL(php_output_default_handler_name), php_output_handler_default_func, chunk_size, flags TSRMLS_CC);
	}
	if (SUCCESS == php_output_handler_start(handler TSRMLS_CC)) {
		return SUCCESS;
	}
	php_output_handler_free(&handler TSRMLS_CC);
	return FAILURE;
}
