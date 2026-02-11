zend_multibyte_set_functions(const zend_multibyte_functions *functions TSRMLS_DC)
{
	zend_multibyte_encoding_utf32be = functions->encoding_fetcher("UTF-32BE" TSRMLS_CC);
	if (!zend_multibyte_encoding_utf32be) {
		return FAILURE;
	}
	zend_multibyte_encoding_utf32le = functions->encoding_fetcher("UTF-32LE" TSRMLS_CC);
	if (!zend_multibyte_encoding_utf32le) {
		return FAILURE;
	}
	zend_multibyte_encoding_utf16be = functions->encoding_fetcher("UTF-16BE" TSRMLS_CC);
	if (!zend_multibyte_encoding_utf16be) {
		return FAILURE;
	}
	zend_multibyte_encoding_utf16le = functions->encoding_fetcher("UTF-16LE" TSRMLS_CC);
	if (!zend_multibyte_encoding_utf16le) {
		return FAILURE;
	}
	zend_multibyte_encoding_utf8 = functions->encoding_fetcher("UTF-8" TSRMLS_CC);
	if (!zend_multibyte_encoding_utf8) {
		return FAILURE;
	}

	multibyte_functions = *functions;


	{
		const char *value = zend_ini_string("zend.script_encoding", sizeof("zend.script_encoding"), 0);
		zend_multibyte_set_script_encoding_by_string(value, strlen(value) TSRMLS_CC);
	}
	return SUCCESS;
}
