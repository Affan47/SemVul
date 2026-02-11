do_bind_inherited_class(const zend_op *opline, HashTable *class_table, zend_class_entry *parent_ce, zend_bool compile_time TSRMLS_DC)
{
	zend_class_entry *ce, **pce;
	int found_ce;

	found_ce = zend_hash_find(class_table, opline->op1.u.constant.value.str.val, opline->op1.u.constant.value.str.len, (void **) &pce);

	if (found_ce == FAILURE) {
		if (!compile_time) {


			zend_error(E_COMPILE_ERROR, "Cannot redeclare class %s", opline->op2.u.constant.value.str.val);
		}
		return NULL;
	} else {
		ce = *pce;
	}

	if (parent_ce->ce_flags & ZEND_ACC_INTERFACE) {
		zend_error(E_COMPILE_ERROR, "Class %s cannot extend from interface %s", ce->name, parent_ce->name);
	}

	zend_do_inheritance(ce, parent_ce TSRMLS_CC);

	ce->refcount++;


	if (zend_hash_add(class_table, opline->op2.u.constant.value.str.val, opline->op2.u.constant.value.str.len+1, pce, sizeof(zend_class_entry *), NULL)==FAILURE) {
		zend_error(E_COMPILE_ERROR, "Cannot redeclare class %s", ce->name);
	}
	return ce;
}
