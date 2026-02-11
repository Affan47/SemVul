php_getimagesize_from_any(INTERNAL_FUNCTION_PARAMETERS, int mode) {
	zval **info = NULL;
	php_stream *stream = NULL;
	char *input;
	int input_len;
	const int argc = ZEND_NUM_ARGS();

	if (zend_parse_parameters(argc TSRMLS_CC, "s|Z", &input, &input_len, &info) == FAILURE) {
			return;
	}

	if (argc == 2) {
			zval_dtor(*info);
			array_init(*info);
	}


	if (mode == FROM_PATH) {
		stream = php_stream_open_wrapper(input, "rb", STREAM_MUST_SEEK|REPORT_ERRORS|IGNORE_PATH, NULL);
	} else {
		stream = php_stream_memory_open(TEMP_STREAM_READONLY, input, input_len);
	}

	if (!stream) {
		   RETURN_FALSE;
	}

	php_getimagesize_from_stream(stream, info, INTERNAL_FUNCTION_PARAM_PASSTHRU);
	php_stream_close(stream);
}
