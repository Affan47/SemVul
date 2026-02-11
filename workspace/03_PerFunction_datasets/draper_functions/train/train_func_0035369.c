generate_free_foreach_copy(const zend_op *foreach_copy TSRMLS_DC)
{
	zend_op *opline;


	if (foreach_copy->result_type == IS_UNUSED && foreach_copy->op1_type == IS_UNUSED) {
		return 1;
	}

	opline = get_next_op(CG(active_op_array) TSRMLS_CC);

	opline->opcode = (foreach_copy->result_type == IS_TMP_VAR) ? ZEND_FREE : ZEND_SWITCH_FREE;
	COPY_NODE(opline->op1, foreach_copy->result);
	SET_UNUSED(opline->op2);
	opline->extended_value = 1;

	if (foreach_copy->op1_type != IS_UNUSED) {
		opline = get_next_op(CG(active_op_array) TSRMLS_CC);

		opline->opcode = (foreach_copy->op1_type == IS_TMP_VAR) ? ZEND_FREE : ZEND_SWITCH_FREE;
		COPY_NODE(opline->op1, foreach_copy->op1);
		SET_UNUSED(opline->op2);
		opline->extended_value = 0;
	}

	return 0;
}
