php_stream_display_wrapper_errors(php_stream_wrapper *wrapper, const char *path, const char *caption TSRMLS_DC)
{
	char *tmp = estrdup(path);
	char *msg;
	int free_msg = 0;

	if (wrapper) {
		zend_llist *err_list = php_get_wrapper_errors_list(wrapper TSRMLS_CC);
		if (err_list) {
			size_t l = 0;
			int brlen;
			int i;
			int count = zend_llist_count(err_list);
			const char *br;
			const char **err_buf_p;
			zend_llist_position pos;

			if (PG(html_errors)) {
				brlen = 7;
				br = "<br />\n";
			} else {
				brlen = 1;
				br = "\n";
			}

			for (err_buf_p = zend_llist_get_first_ex(err_list, &pos), i = 0;
					err_buf_p;
					err_buf_p = zend_llist_get_next_ex(err_list, &pos), i++) {
				l += strlen(*err_buf_p);
				if (i < count - 1) {
					l += brlen;
				}
			}
			msg = emalloc(l + 1);
			msg[0] = '\0';
			for (err_buf_p = zend_llist_get_first_ex(err_list, &pos), i = 0;
					err_buf_p;
					err_buf_p = zend_llist_get_next_ex(err_list, &pos), i++) {
				strcat(msg, *err_buf_p);
				if (i < count - 1) {
					strcat(msg, br);
				}
			}

			free_msg = 1;
		} else {
			if (wrapper == &php_plain_files_wrapper) {
				msg = strerror(errno);
			} else {
				msg = "operation failed";
			}
		}
	} else {
		msg = "no suitable wrapper could be found";
	}

	php_strip_url_passwd(tmp);
	php_error_docref1(NULL TSRMLS_CC, tmp, E_WARNING, "%s: %s", caption, msg);
	efree(tmp);
	if (free_msg) {
		efree(msg);
	}
}
