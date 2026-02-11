execute_new_code(TSRMLS_D)
{
	zend_op *opline, *end;
	zend_op *ret_opline;
	int orig_interactive;

	if (!(CG(active_op_array)->fn_flags & ZEND_ACC_INTERACTIVE)
		|| CG(active_op_array)->backpatch_count>0
		|| CG(active_op_array)->function_name
		|| CG(active_op_array)->type!=ZEND_USER_FUNCTION) {
		return;
	}

	ret_opline = get_next_op(CG(active_op_array) TSRMLS_CC);
	ret_opline->opcode = ZEND_RETURN;
	ret_opline->op1.op_type = IS_CONST;
	INIT_ZVAL(ret_opline->op1.u.constant);
	SET_UNUSED(ret_opline->op2);

	if (!CG(active_op_array)->start_op) {
		CG(active_op_array)->start_op = CG(active_op_array)->opcodes;
	}

	opline=CG(active_op_array)->start_op;
	end=CG(active_op_array)->opcodes+CG(active_op_array)->last;

	while (opline<end) {
		if (opline->op1.op_type == IS_CONST) {
			Z_SET_ISREF(opline->op1.u.constant);
			Z_SET_REFCOUNT(opline->op1.u.constant, 2);
		}
		if (opline->op2.op_type == IS_CONST) {
			Z_SET_ISREF(opline->op2.u.constant);
			Z_SET_REFCOUNT(opline->op2.u.constant, 2);
		}
		switch (opline->opcode) {
			case ZEND_GOTO:
				if (Z_TYPE(opline->op2.u.constant) != IS_LONG) {
					zend_resolve_goto_label(CG(active_op_array), opline, 1 TSRMLS_CC);
				}

			case ZEND_JMP:
				opline->op1.u.jmp_addr = &CG(active_op_array)->opcodes[opline->op1.u.opline_num];
				break;
			case ZEND_JMPZ:
			case ZEND_JMPNZ:
			case ZEND_JMPZ_EX:
			case ZEND_JMPNZ_EX:
			case ZEND_JMP_SET:
				opline->op2.u.jmp_addr = &CG(active_op_array)->opcodes[opline->op2.u.opline_num];
				break;
		}
		ZEND_VM_SET_OPCODE_HANDLER(opline);
		opline++;
	}

	zend_release_labels(TSRMLS_C);

	EG(return_value_ptr_ptr) = NULL;
	EG(active_op_array) = CG(active_op_array);
	orig_interactive = CG(interactive);
	CG(interactive) = 0;
	zend_execute(CG(active_op_array) TSRMLS_CC);
	CG(interactive) = orig_interactive;

	if (EG(exception)) {
		zend_exception_error(EG(exception), E_ERROR TSRMLS_CC);
	}

	CG(active_op_array)->last -= 1;
	CG(active_op_array)->start_op = CG(active_op_array)->opcodes+CG(active_op_array)->last;
}
