php_userstreamop_readdir(php_stream *stream, char *buf, size_t count TSRMLS_DC)
{
	zval func_name;
	zval *retval = NULL;
	int call_result;
	size_t didread = 0;
	php_userstream_data_t *us = (php_userstream_data_t *)stream->abstract;
	php_stream_dirent *ent = (php_stream_dirent*)buf;


	if (count != sizeof(php_stream_dirent))
		return 0;

	ZVAL_STRINGL(&func_name, USERSTREAM_DIR_READ, sizeof(USERSTREAM_DIR_READ)-1, 0);

	call_result = call_user_function_ex(NULL,
			&us->object,
			&func_name,
			&retval,
			0, NULL,
			0, NULL TSRMLS_CC);

	if (call_result == SUCCESS && retval != NULL && Z_TYPE_P(retval) != IS_BOOL) {
		convert_to_string(retval);
		PHP_STRLCPY(ent->d_name, Z_STRVAL_P(retval), sizeof(ent->d_name), Z_STRLEN_P(retval));

		didread = sizeof(php_stream_dirent);
	} else if (call_result == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s::" USERSTREAM_DIR_READ " is not implemented!",
				us->wrapper->classname);
	}

	if (retval)
		zval_ptr_dtor(&retval);

	return didread;
}
