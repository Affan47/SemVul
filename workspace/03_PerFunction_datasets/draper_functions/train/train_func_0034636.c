zend_do_inheritance(zend_class_entry *ce, zend_class_entry *parent_ce TSRMLS_DC)
{
	if ((ce->ce_flags & ZEND_ACC_INTERFACE)
		&& !(parent_ce->ce_flags & ZEND_ACC_INTERFACE)) {
		zend_error(E_COMPILE_ERROR, "Interface %s may not inherit from class (%s)", ce->name, parent_ce->name);
	}
	if (parent_ce->ce_flags & ZEND_ACC_FINAL_CLASS) {
		zend_error(E_COMPILE_ERROR, "Class %s may not inherit from final class (%s)", ce->name, parent_ce->name);
	}

	ce->parent = parent_ce;

	if (!ce->serialize) {
		ce->serialize   = parent_ce->serialize;
	}
	if (!ce->unserialize) {
		ce->unserialize = parent_ce->unserialize;
	}


	zend_do_inherit_interfaces(ce, parent_ce TSRMLS_CC);


	zend_hash_merge(&ce->default_properties, &parent_ce->default_properties, zval_property_ctor(parent_ce, ce), NULL, sizeof(zval *), 0);
	if (parent_ce->type != ce->type) {

		zend_update_class_constants(parent_ce  TSRMLS_CC);
		zend_hash_apply_with_arguments(CE_STATIC_MEMBERS(parent_ce) TSRMLS_CC, (apply_func_args_t)inherit_static_prop, 1, &ce->default_static_members);
	} else {
		zend_hash_apply_with_arguments(&parent_ce->default_static_members TSRMLS_CC, (apply_func_args_t)inherit_static_prop, 1, &ce->default_static_members);
	}
	zend_hash_merge_ex(&ce->properties_info, &parent_ce->properties_info, (copy_ctor_func_t) (ce->type & ZEND_INTERNAL_CLASS ? zend_duplicate_property_info_internal : zend_duplicate_property_info), sizeof(zend_property_info), (merge_checker_func_t) do_inherit_property_access_check, ce);

	zend_hash_merge(&ce->constants_table, &parent_ce->constants_table, zval_property_ctor(parent_ce, ce), NULL, sizeof(zval *), 0);
	zend_hash_merge_ex(&ce->function_table, &parent_ce->function_table, (copy_ctor_func_t) do_inherit_method, sizeof(zend_function), (merge_checker_func_t) do_inherit_method_check, ce);
	do_inherit_parent_constructor(ce);

	if (ce->ce_flags & ZEND_ACC_IMPLICIT_ABSTRACT_CLASS && ce->type == ZEND_INTERNAL_CLASS) {
		ce->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
	} else if (!(ce->ce_flags & ZEND_ACC_IMPLEMENT_INTERFACES)) {

		zend_verify_abstract_class(ce TSRMLS_CC);
	}
}
