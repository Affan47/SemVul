php_userstreamop_flush(php_stream *stream TSRMLS_DC)
{
	zval func_name;
	zval *retval = NULL;
	int call_result;
	php_userstream_data_t *us = (php_userstream_data_t *)stream->abstract;

	assert(us != NULL);

	ZVAL_STRINGL(&func_name, USERSTREAM_FLUSH, sizeof(USERSTREAM_FLUSH)-1, 0);

	call_result = call_user_function_ex(NULL,
			&us->object,
			&func_name,
			&retval,
			0, NULL, 0, NULL TSRMLS_CC);

	if (call_result == SUCCESS && retval != NULL && zval_is_true(retval))
		call_result = 0;
	else
		call_result = -1;

	if (retval)
		zval_ptr_dtor(&retval);

	return call_result;
}
