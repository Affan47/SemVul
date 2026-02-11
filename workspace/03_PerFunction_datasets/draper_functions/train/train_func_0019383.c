zend_do_for_before_statement(const znode *cond_start, const znode *second_semicolon_token TSRMLS_DC)
{
	zend_op *opline = get_next_op(CG(active_op_array) TSRMLS_CC);

	opline->opcode = ZEND_JMP;
	opline->op1.opline_num = cond_start->u.op.opline_num;
	CG(active_op_array)->opcodes[second_semicolon_token->u.op.opline_num].extended_value = get_next_op_number(CG(active_op_array));
	SET_UNUSED(opline->op1);
	SET_UNUSED(opline->op2);

	do_begin_loop(TSRMLS_C);

	INC_BPC(CG(active_op_array));
}
