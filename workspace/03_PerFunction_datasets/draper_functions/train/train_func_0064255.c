php_plain_files_mkdir(php_stream_wrapper *wrapper, char *dir, int mode, int options, php_stream_context *context TSRMLS_DC)
{
	int ret, recursive = options & PHP_STREAM_MKDIR_RECURSIVE;
	char *p;

	if ((p = strstr(dir, "://")) != NULL) {
		dir = p + 3;
	}

	if (!recursive) {
		ret = php_mkdir(dir, mode TSRMLS_CC);
	} else {

		char *e;
		struct stat sb;
		int dir_len = strlen(dir);
		int offset = 0;
		char buf[MAXPATHLEN];

		if (!expand_filepath_with_mode(dir, buf, NULL, 0, CWD_EXPAND  TSRMLS_CC)) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid path");
			return 0;
		}

		e = buf +  strlen(buf);

		if ((p = memchr(buf, DEFAULT_SLASH, dir_len))) {
			offset = p - buf + 1;
		}

		if (p && dir_len == 1) {

		}
		else {

			while ( (p = strrchr(buf + offset, DEFAULT_SLASH)) || (offset != 1 && (p = strrchr(buf, DEFAULT_SLASH))) ) {
				int n = 0;

				*p = '\0';
				while (p > buf && *(p-1) == DEFAULT_SLASH) {
					++n;
					--p;
					*p = '\0';
				}
				if (VCWD_STAT(buf, &sb) == 0) {
					while (1) {
						*p = DEFAULT_SLASH;
						if (!n) break;
						--n;
						++p;
					}
					break;
				}
			}
		}

		if (p == buf) {
			ret = php_mkdir(dir, mode TSRMLS_CC);
		} else if (!(ret = php_mkdir(buf, mode TSRMLS_CC))) {
			if (!p) {
				p = buf;
			}

			while (++p != e) {
				if (*p == '\0') {
					*p = DEFAULT_SLASH;
					if ((*(p+1) != '\0') &&
						(ret = VCWD_MKDIR(buf, (mode_t)mode)) < 0) {
						if (options & REPORT_ERRORS) {
							php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", strerror(errno));
						}
						break;
					}
				}
			}
		}
	}
	if (ret < 0) {

		return 0;
	} else {

		return 1;
	}
}
