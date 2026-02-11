zend_do_fetch_property(znode *result, znode *object, const znode *property TSRMLS_DC)
{
	zend_op opline;
	zend_llist *fetch_list_ptr;

	zend_stack_top(&CG(bp_stack), (void **) &fetch_list_ptr);

	if (object->op_type == IS_CV) {
		if (object->u.var == CG(active_op_array)->this_var) {
			SET_UNUSED(*object);
		}
	} else if (fetch_list_ptr->count == 1) {
		zend_llist_element *le = fetch_list_ptr->head;
		zend_op *opline_ptr = (zend_op *) le->data;

		if (opline_is_fetch_this(opline_ptr TSRMLS_CC)) {
			efree(Z_STRVAL(opline_ptr->op1.u.constant));
			SET_UNUSED(opline_ptr->op1);
			opline_ptr->op2 = *property;

			switch (opline_ptr->opcode) {
				case ZEND_FETCH_W:
					opline_ptr->opcode = ZEND_FETCH_OBJ_W;
					break;
				case ZEND_FETCH_R:
					opline_ptr->opcode = ZEND_FETCH_OBJ_R;
					break;
				case ZEND_FETCH_RW:
					opline_ptr->opcode = ZEND_FETCH_OBJ_RW;
					break;
				case ZEND_FETCH_IS:
					opline_ptr->opcode = ZEND_FETCH_OBJ_IS;
					break;
				case ZEND_FETCH_UNSET:
					opline_ptr->opcode = ZEND_FETCH_OBJ_UNSET;
					break;
				case ZEND_FETCH_FUNC_ARG:
					opline_ptr->opcode = ZEND_FETCH_OBJ_FUNC_ARG;
					break;
			}
			*result = opline_ptr->result;
			return;
		}
	}

	init_op(&opline TSRMLS_CC);
	opline.opcode = ZEND_FETCH_OBJ_W;
	opline.result.op_type = IS_VAR;
	opline.result.u.EA.type = 0;
	opline.result.u.var = get_temporary_variable(CG(active_op_array));
	opline.op1 = *object;
	opline.op2 = *property;
	*result = opline.result;

	zend_llist_add_element(fetch_list_ptr, &opline);
}
