pdo_hash_methods(pdo_dbh_t *dbh, int kind TSRMLS_DC)
{
	const zend_function_entry *funcs;
	zend_function func;
	zend_internal_function *ifunc = (zend_internal_function*)&func;
	int namelen;
	char *lc_name;

	if (!dbh || !dbh->methods || !dbh->methods->get_driver_methods) {
		return 0;
	}
	funcs =	dbh->methods->get_driver_methods(dbh, kind TSRMLS_CC);
	if (!funcs) {
		return 0;
	}

	if (!(dbh->cls_methods[kind] = pemalloc(sizeof(HashTable), dbh->is_persistent))) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "out of memory while allocating PDO methods.");
	}
	zend_hash_init_ex(dbh->cls_methods[kind], 8, NULL, NULL, dbh->is_persistent, 0);

	while (funcs->fname) {
		ifunc->type = ZEND_INTERNAL_FUNCTION;
		ifunc->handler = funcs->handler;
		ifunc->function_name = (char*)funcs->fname;
		ifunc->scope = dbh->std.ce;
		ifunc->prototype = NULL;
		if (funcs->flags) {
			ifunc->fn_flags = funcs->flags | ZEND_ACC_NEVER_CACHE;
		} else {
			ifunc->fn_flags = ZEND_ACC_PUBLIC | ZEND_ACC_NEVER_CACHE;
		}
		if (funcs->arg_info) {
			zend_internal_function_info *info = (zend_internal_function_info*)funcs->arg_info;

			ifunc->arg_info = (zend_arg_info*)funcs->arg_info + 1;
			ifunc->num_args = funcs->num_args;
			if (info->required_num_args == -1) {
				ifunc->required_num_args = funcs->num_args;
			} else {
				ifunc->required_num_args = info->required_num_args;
			}
			if (info->pass_rest_by_reference) {
				if (info->pass_rest_by_reference == ZEND_SEND_PREFER_REF) {
					ifunc->fn_flags |= ZEND_ACC_PASS_REST_PREFER_REF;
				} else {
					ifunc->fn_flags |= ZEND_ACC_PASS_REST_BY_REFERENCE;
				}
			}
			if (info->return_reference) {
				ifunc->fn_flags |= ZEND_ACC_RETURN_REFERENCE;
			}
		} else {
			ifunc->arg_info = NULL;
			ifunc->num_args = 0;
			ifunc->required_num_args = 0;
		}
		namelen = strlen(funcs->fname);
		lc_name = emalloc(namelen+1);
		zend_str_tolower_copy(lc_name, funcs->fname, namelen);
		zend_hash_add(dbh->cls_methods[kind], lc_name, namelen+1, &func, sizeof(func), NULL);
		efree(lc_name);
		funcs++;
	}

	return 1;
}
