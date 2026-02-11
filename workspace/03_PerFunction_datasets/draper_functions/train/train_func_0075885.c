do_bind_class(const zend_op *opline, HashTable *class_table, zend_bool compile_time TSRMLS_DC)
{
	zend_class_entry *ce, **pce;

	if (zend_hash_find(class_table, opline->op1.u.constant.value.str.val, opline->op1.u.constant.value.str.len, (void **) &pce)==FAILURE) {
		zend_error(E_COMPILE_ERROR, "Internal Zend error - Missing class information for %s", opline->op1.u.constant.value.str.val);
		return NULL;
	} else {
		ce = *pce;
	}
	ce->refcount++;
	if (zend_hash_add(class_table, opline->op2.u.constant.value.str.val, opline->op2.u.constant.value.str.len+1, &ce, sizeof(zend_class_entry *), NULL)==FAILURE) {
		ce->refcount--;
		if (!compile_time) {


			zend_error(E_COMPILE_ERROR, "Cannot redeclare class %s", ce->name);
		}
		return NULL;
	} else {
		if (!(ce->ce_flags & (ZEND_ACC_INTERFACE|ZEND_ACC_IMPLEMENT_INTERFACES))) {
			zend_verify_abstract_class(ce TSRMLS_CC);
		}
		return ce;
	}
}
