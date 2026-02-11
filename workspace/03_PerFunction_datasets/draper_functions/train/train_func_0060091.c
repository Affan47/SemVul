zend_do_indirect_references(znode *result, const znode *num_references, znode *variable TSRMLS_DC)
{
	int i;

	zend_do_end_variable_parse(variable, BP_VAR_R, 0 TSRMLS_CC);
	for (i=1; i<num_references->u.constant.value.lval; i++) {
		fetch_simple_variable_ex(result, variable, 0, ZEND_FETCH_R TSRMLS_CC);
		*variable = *result;
	}
	zend_do_begin_variable_parse(TSRMLS_C);
	fetch_simple_variable(result, variable, 1 TSRMLS_CC);
}
