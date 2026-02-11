zend_do_do_while_begin(TSRMLS_D)
{
	do_begin_loop(TSRMLS_C);
	INC_BPC(CG(active_op_array));
}
