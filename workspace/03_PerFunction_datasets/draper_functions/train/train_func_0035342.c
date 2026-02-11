zend_do_foreach_begin(znode *foreach_token, znode *open_brackets_token, znode *array, znode *as_token, int variable TSRMLS_DC)
{
	zend_op *opline;
	zend_bool is_variable;
	zend_bool push_container = 0;
	zend_op dummy_opline;

	if (variable) {
		if (zend_is_function_or_method_call(array)) {
			is_variable = 0;
		} else {
			is_variable = 1;
		}

		open_brackets_token->u.op.opline_num = get_next_op_number(CG(active_op_array));
		zend_do_end_variable_parse(array, BP_VAR_W, 0 TSRMLS_CC);
		if (CG(active_op_array)->last > 0 &&
		    CG(active_op_array)->opcodes[CG(active_op_array)->last-1].opcode == ZEND_FETCH_OBJ_W) {

			if (CG(active_op_array)->opcodes[CG(active_op_array)->last-1].op1_type == IS_VAR) {
				CG(active_op_array)->opcodes[CG(active_op_array)->last-1].extended_value |= ZEND_FETCH_ADD_LOCK;
				push_container = 1;
			}
		}
	} else {
		is_variable = 0;
		open_brackets_token->u.op.opline_num = get_next_op_number(CG(active_op_array));
	}


	foreach_token->u.op.opline_num = get_next_op_number(CG(active_op_array));

	opline = get_next_op(CG(active_op_array) TSRMLS_CC);


	opline->opcode = ZEND_FE_RESET;
	opline->result_type = IS_VAR;
	opline->result.var = get_temporary_variable(CG(active_op_array));
	SET_NODE(opline->op1, array);
	SET_UNUSED(opline->op2);
	opline->extended_value = is_variable ? ZEND_FE_RESET_VARIABLE : 0;

	COPY_NODE(dummy_opline.result, opline->result);
	if (push_container) {
		COPY_NODE(dummy_opline.op1, CG(active_op_array)->opcodes[CG(active_op_array)->last-2].op1);
	} else {
		dummy_opline.op1_type = IS_UNUSED;
	}
	zend_stack_push(&CG(foreach_copy_stack), (void *) &dummy_opline, sizeof(zend_op));


	as_token->u.op.opline_num = get_next_op_number(CG(active_op_array));

	opline = get_next_op(CG(active_op_array) TSRMLS_CC);
	opline->opcode = ZEND_FE_FETCH;
	opline->result_type = IS_VAR;
	opline->result.var = get_temporary_variable(CG(active_op_array));
	COPY_NODE(opline->op1, dummy_opline.result);
	opline->extended_value = 0;
	SET_UNUSED(opline->op2);

	opline = get_next_op(CG(active_op_array) TSRMLS_CC);
	opline->opcode = ZEND_OP_DATA;
	SET_UNUSED(opline->op1);
	SET_UNUSED(opline->op2);
	SET_UNUSED(opline->result);
}
