_php_stream_mkdir(char *path, int mode, int options, php_stream_context *context TSRMLS_DC)
{
	php_stream_wrapper *wrapper = NULL;

	wrapper = php_stream_locate_url_wrapper(path, NULL, ENFORCE_SAFE_MODE TSRMLS_CC);
	if (!wrapper || !wrapper->wops || !wrapper->wops->stream_mkdir) {
		return 0;
	}

	return wrapper->wops->stream_mkdir(wrapper, path, mode, options, context TSRMLS_CC);
}
