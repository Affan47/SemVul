do_inherit_method_check(HashTable *child_function_table, zend_function *parent, const zend_hash_key *hash_key, zend_class_entry *child_ce)
{
	zend_uint parent_flags = parent->common.fn_flags;
	zend_function *child;
	TSRMLS_FETCH();

	if (zend_hash_quick_find(child_function_table, hash_key->arKey, hash_key->nKeyLength, hash_key->h, (void **) &child)==FAILURE) {
		if (parent_flags & (ZEND_ACC_ABSTRACT)) {
			child_ce->ce_flags |= ZEND_ACC_IMPLICIT_ABSTRACT_CLASS;
		}
		return 1;
	}

	do_inheritance_check_on_method(child, parent TSRMLS_CC);

	return 0;
}
