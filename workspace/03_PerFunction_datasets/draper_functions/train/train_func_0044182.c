php_plain_files_rename(php_stream_wrapper *wrapper, char *url_from, char *url_to, int options, php_stream_context *context TSRMLS_DC)
{
	char *p;
	int ret;

	if (!url_from || !url_to) {
		return 0;
	}

#ifdef PHP_WIN32
	if (!php_win32_check_trailing_space(url_from, strlen(url_from))) {
		php_win32_docref2_from_error(ERROR_INVALID_NAME, url_from, url_to TSRMLS_CC);
		return 0;
	}
	if (!php_win32_check_trailing_space(url_to, strlen(url_to))) {
		php_win32_docref2_from_error(ERROR_INVALID_NAME, url_from, url_to TSRMLS_CC);
		return 0;
	}
#endif

	if ((p = strstr(url_from, "://")) != NULL) {
		url_from = p + 3;
	}

	if ((p = strstr(url_to, "://")) != NULL) {
		url_to = p + 3;
	}

	if (php_check_open_basedir(url_from TSRMLS_CC) || php_check_open_basedir(url_to TSRMLS_CC)) {
		return 0;
	}

	ret = VCWD_RENAME(url_from, url_to);

	if (ret == -1) {
#ifndef PHP_WIN32
# ifdef EXDEV
		if (errno == EXDEV) {
			struct stat sb;
			if (php_copy_file(url_from, url_to TSRMLS_CC) == SUCCESS) {
				if (VCWD_STAT(url_from, &sb) == 0) {
#  if !defined(TSRM_WIN32) && !defined(NETWARE)
					if (VCWD_CHMOD(url_to, sb.st_mode)) {
						if (errno == EPERM) {
							php_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
							VCWD_UNLINK(url_from);
							return 1;
						}
						php_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
						return 0;
					}
					if (VCWD_CHOWN(url_to, sb.st_uid, sb.st_gid)) {
						if (errno == EPERM) {
							php_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
							VCWD_UNLINK(url_from);
							return 1;
						}
						php_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
						return 0;
					}
#  endif
					VCWD_UNLINK(url_from);
					return 1;
				}
			}
			php_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
			return 0;
		}
# endif
#endif

#ifdef PHP_WIN32
		php_win32_docref2_from_error(GetLastError(), url_from, url_to TSRMLS_CC);
#else
		php_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
#endif
		return 0;
	}


	php_clear_stat_cache(1, NULL, 0 TSRMLS_CC);

	return 1;
}
