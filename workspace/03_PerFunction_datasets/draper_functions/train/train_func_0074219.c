php_rshutdown_session_globals(TSRMLS_D)
{
	if (PS(http_session_vars)) {
		zval_ptr_dtor(&PS(http_session_vars));
		PS(http_session_vars) = NULL;
	}

	if (PS(mod_data)) {
		zend_try {
			PS(mod)->s_close(&PS(mod_data) TSRMLS_CC);
		} zend_end_try();
	}
	if (PS(id)) {
		efree(PS(id));
	}
}
