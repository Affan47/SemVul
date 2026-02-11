php_handle_wbmp(php_stream * stream TSRMLS_DC)
{
	struct gfxinfo *result = (struct gfxinfo *) ecalloc(1, sizeof(struct gfxinfo));

	if (!php_get_wbmp(stream, &result, 0 TSRMLS_CC)) {
		efree(result);
		return NULL;
	}

	return result;
}
