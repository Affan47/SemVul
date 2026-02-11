zend_std_call_user_call(INTERNAL_FUNCTION_PARAMETERS)
{
	zend_internal_function *func = (zend_internal_function *)EG(current_execute_data)->function_state.function;
	zval *method_name_ptr, *method_args_ptr;
	zval *method_result_ptr = NULL;
	zend_class_entry *ce = Z_OBJCE_P(this_ptr);

	ALLOC_ZVAL(method_args_ptr);
	INIT_PZVAL(method_args_ptr);
	array_init_size(method_args_ptr, ZEND_NUM_ARGS());

	if (UNEXPECTED(zend_copy_parameters_array(ZEND_NUM_ARGS(), method_args_ptr TSRMLS_CC) == FAILURE)) {
		zval_dtor(method_args_ptr);
		zend_error_noreturn(E_ERROR, "Cannot get arguments for __call");
		RETURN_FALSE;
	}

	ALLOC_ZVAL(method_name_ptr);
	INIT_PZVAL(method_name_ptr);
	ZVAL_STRING(method_name_ptr, func->function_name, 0);


	zend_call_method_with_2_params(&this_ptr, ce, &ce->__call, ZEND_CALL_FUNC_NAME, &method_result_ptr, method_name_ptr, method_args_ptr);

	if (method_result_ptr) {
		if (Z_ISREF_P(method_result_ptr) || Z_REFCOUNT_P(method_result_ptr) > 1) {
			RETVAL_ZVAL(method_result_ptr, 1, 1);
		} else {
			RETVAL_ZVAL(method_result_ptr, 0, 1);
		}
	}


	zval_ptr_dtor(&method_args_ptr);
	zval_ptr_dtor(&method_name_ptr);


	efree(func);
}
