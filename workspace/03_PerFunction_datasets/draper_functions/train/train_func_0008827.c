php_cli_server_dispatch_router(php_cli_server *server, php_cli_server_client *client TSRMLS_DC)
{
	int decline = 0;
	if (!php_handle_special_queries(TSRMLS_C)) {
		zend_file_handle zfd;
		char *old_cwd;

		ALLOCA_FLAG(use_heap)
		old_cwd = do_alloca(MAXPATHLEN, use_heap);
		old_cwd[0] = '\0';
		php_ignore_value(VCWD_GETCWD(old_cwd, MAXPATHLEN - 1));

		zfd.type = ZEND_HANDLE_FILENAME;
		zfd.filename = server->router;
		zfd.handle.fp = NULL;
		zfd.free_filename = 0;
		zfd.opened_path = NULL;

		zend_try {
			zval *retval = NULL;
			if (SUCCESS == zend_execute_scripts(ZEND_REQUIRE TSRMLS_CC, &retval, 1, &zfd)) {
				if (retval) {
					decline = Z_TYPE_P(retval) == IS_BOOL && !Z_LVAL_P(retval);
					zval_ptr_dtor(&retval);
				}
			} else {
				decline = 1;
			}
		} zend_end_try();

		if (old_cwd[0] != '\0') {
			php_ignore_value(VCWD_CHDIR(old_cwd));
		}

		free_alloca(old_cwd, use_heap);
	}

	return decline;
}
