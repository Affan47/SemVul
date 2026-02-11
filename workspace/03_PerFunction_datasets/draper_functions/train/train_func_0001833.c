shutdown_executor(TSRMLS_D)
{
	zend_try {


		zend_llist_apply(&zend_extensions, (llist_apply_func_t) zend_extension_deactivator TSRMLS_CC);
		zend_hash_graceful_reverse_destroy(&EG(symbol_table));
	} zend_end_try();

	zend_try {
		zval *zeh;


		if (EG(user_error_handler)) {
			zeh = EG(user_error_handler);
			EG(user_error_handler) = NULL;
			zval_ptr_dtor(&zeh);
		}

		if (EG(user_exception_handler)) {
			zeh = EG(user_exception_handler);
			EG(user_exception_handler) = NULL;
			zval_ptr_dtor(&zeh);
		}

		zend_stack_destroy(&EG(user_error_handlers_error_reporting));
		zend_stack_init(&EG(user_error_handlers_error_reporting));
		zend_ptr_stack_clean(&EG(user_error_handlers), ZVAL_DESTRUCTOR, 1);
		zend_ptr_stack_clean(&EG(user_exception_handlers), ZVAL_DESTRUCTOR, 1);
	} zend_end_try();

	zend_try {


		if (EG(full_tables_cleanup)) {
			zend_hash_apply(EG(function_table), (apply_func_t) zend_cleanup_function_data_full TSRMLS_CC);
		} else {
			zend_hash_reverse_apply(EG(function_table), (apply_func_t) zend_cleanup_function_data TSRMLS_CC);
		}
		zend_hash_apply(EG(class_table), (apply_func_t) zend_cleanup_class_data TSRMLS_CC);
	} zend_end_try();

	zend_try {
		zend_vm_stack_destroy(TSRMLS_C);

		zend_objects_store_free_object_storage(&EG(objects_store) TSRMLS_CC);


		if (EG(full_tables_cleanup)) {
			zend_hash_apply(EG(function_table), (apply_func_t) clean_non_persistent_function_full TSRMLS_CC);
			zend_hash_apply(EG(class_table), (apply_func_t) clean_non_persistent_class_full TSRMLS_CC);
		} else {
			zend_hash_reverse_apply(EG(function_table), (apply_func_t) clean_non_persistent_function TSRMLS_CC);
			zend_hash_reverse_apply(EG(class_table), (apply_func_t) clean_non_persistent_class TSRMLS_CC);
		}

		while (EG(symtable_cache_ptr)>=EG(symtable_cache)) {
			zend_hash_destroy(*EG(symtable_cache_ptr));
			FREE_HASHTABLE(*EG(symtable_cache_ptr));
			EG(symtable_cache_ptr)--;
		}
	} zend_end_try();

	zend_try {
		clean_non_persistent_constants(TSRMLS_C);
	} zend_end_try();

	zend_try {
#if 0&&ZEND_DEBUG
	signal(SIGSEGV, original_sigsegv_handler);
#endif

		zend_hash_destroy(&EG(included_files));

		zend_ptr_stack_destroy(&EG(arg_types_stack));
		zend_stack_destroy(&EG(user_error_handlers_error_reporting));
		zend_ptr_stack_destroy(&EG(user_error_handlers));
		zend_ptr_stack_destroy(&EG(user_exception_handlers));
		zend_objects_store_destroy(&EG(objects_store));
		if (EG(in_autoload)) {
			zend_hash_destroy(EG(in_autoload));
			FREE_HASHTABLE(EG(in_autoload));
		}
	} zend_end_try();

	zend_shutdown_fpu(TSRMLS_C);

	EG(active) = 0;
}
