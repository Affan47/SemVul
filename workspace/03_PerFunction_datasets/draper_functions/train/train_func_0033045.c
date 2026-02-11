php_handle_aborted_connection(void)
{
	TSRMLS_FETCH();

	PG(connection_status) = PHP_CONNECTION_ABORTED;
	php_output_set_status(PHP_OUTPUT_DISABLED TSRMLS_CC);

	if (!PG(ignore_user_abort)) {
		zend_bailout();
	}
}
