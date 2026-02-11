php_plain_files_url_stater(php_stream_wrapper *wrapper, char *url, int flags, php_stream_statbuf *ssb, php_stream_context *context TSRMLS_DC)
{

	if (strncmp(url, "file://", sizeof("file://") - 1) == 0) {
		url += sizeof("file://") - 1;
	}

	if (PG(safe_mode) &&(!php_checkuid_ex(url, NULL, CHECKUID_CHECK_FILE_AND_DIR, (flags & PHP_STREAM_URL_STAT_QUIET) ? CHECKUID_NO_ERRORS : 0))) {
		return -1;
	}

	if (php_check_open_basedir_ex(url, (flags & PHP_STREAM_URL_STAT_QUIET) ? 0 : 1 TSRMLS_CC)) {
		return -1;
	}

#ifdef HAVE_SYMLINK
	if (flags & PHP_STREAM_URL_STAT_LINK) {
		return VCWD_LSTAT(url, &ssb->sb);
	} else
#endif
		return VCWD_STAT(url, &ssb->sb);
}
