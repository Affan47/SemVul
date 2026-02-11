zend_do_fetch_global_variable(znode *varname, const znode *static_assignment, int fetch_type TSRMLS_DC)
{
	zend_op *opline;
	znode lval;
	znode result;

	if (varname->op_type == IS_CONST) {
		if (Z_TYPE(varname->u.constant) != IS_STRING) {
			convert_to_string(&varname->u.constant);
		}
	}

	opline = get_next_op(CG(active_op_array) TSRMLS_CC);
	opline->opcode = ZEND_FETCH_W;
	opline->result_type = IS_VAR;
	opline->result.var = get_temporary_variable(CG(active_op_array));
	SET_NODE(opline->op1, varname);
	if (opline->op1_type == IS_CONST) {
		CALCULATE_LITERAL_HASH(opline->op1.constant);
	}
	SET_UNUSED(opline->op2);
	opline->extended_value = fetch_type;
	GET_NODE(&result, opline->result);

	if (varname->op_type == IS_CONST) {
		zval_copy_ctor(&varname->u.constant);
	}
	fetch_simple_variable(&lval, varname, 0 TSRMLS_CC);

	zend_do_assign_ref(NULL, &lval, &result TSRMLS_CC);
	CG(active_op_array)->opcodes[CG(active_op_array)->last-1].result_type |= EXT_TYPE_UNUSED;
}
