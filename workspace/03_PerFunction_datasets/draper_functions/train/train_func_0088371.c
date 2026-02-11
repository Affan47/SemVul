do_bind_inherited_class(const zend_op_array *op_array, const zend_op *opline, HashTable *class_table, zend_class_entry *parent_ce, zend_bool compile_time TSRMLS_DC)
{
	zend_class_entry *ce, **pce;
	int found_ce;
	zval *op1, *op2;

	if (compile_time) {
		op1 = &CONSTANT_EX(op_array, opline->op1.constant);
		op2 = &CONSTANT_EX(op_array, opline->op2.constant);
	} else {
		op1 = opline->op1.zv;
		op2 = opline->op2.zv;
	}

	found_ce = zend_hash_quick_find(class_table, Z_STRVAL_P(op1), Z_STRLEN_P(op1), Z_HASH_P(op1), (void **) &pce);

	if (found_ce == FAILURE) {
		if (!compile_time) {


			zend_error(E_COMPILE_ERROR, "Cannot redeclare class %s", Z_STRVAL_P(op2));
		}
		return NULL;
	} else {
		ce = *pce;
	}

	if (parent_ce->ce_flags & ZEND_ACC_INTERFACE) {
		zend_error(E_COMPILE_ERROR, "Class %s cannot extend from interface %s", ce->name, parent_ce->name);
	} else if ((parent_ce->ce_flags & ZEND_ACC_TRAIT) == ZEND_ACC_TRAIT) {
		zend_error(E_COMPILE_ERROR, "Class %s cannot extend from trait %s", ce->name, parent_ce->name);
	}

	zend_do_inheritance(ce, parent_ce TSRMLS_CC);

	ce->refcount++;


	if (zend_hash_quick_add(class_table, Z_STRVAL_P(op2), Z_STRLEN_P(op2)+1, Z_HASH_P(op2), pce, sizeof(zend_class_entry *), NULL)==FAILURE) {
		zend_error(E_COMPILE_ERROR, "Cannot redeclare class %s", ce->name);
	}
	return ce;
}
