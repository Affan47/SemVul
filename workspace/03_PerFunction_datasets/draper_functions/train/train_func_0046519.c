zend_add_trait_method(zend_class_entry *ce, const char *name, const char *arKey, uint nKeyLength, zend_function *fn, HashTable **overriden TSRMLS_DC)
{
	zend_function *existing_fn = NULL;
	ulong h = zend_hash_func(arKey, nKeyLength);

	if (zend_hash_quick_find(&ce->function_table, arKey, nKeyLength, h, (void**) &existing_fn) == SUCCESS) {
		if (existing_fn->common.scope == ce) {


			if (*overriden) {
				if (zend_hash_quick_find(*overriden, arKey, nKeyLength, h, (void**) &existing_fn) == SUCCESS) {
					if (existing_fn->common.fn_flags & ZEND_ACC_ABSTRACT) {

						if (!zend_traits_method_compatibility_check(fn, existing_fn TSRMLS_CC)) {
							zend_error(E_COMPILE_ERROR, "Declaration of %s must be compatible with %s",
								zend_get_function_declaration(fn TSRMLS_CC),
								zend_get_function_declaration(existing_fn TSRMLS_CC));
						}
					} else if (fn->common.fn_flags & ZEND_ACC_ABSTRACT) {

						if (!zend_traits_method_compatibility_check(existing_fn, fn TSRMLS_CC)) {
							zend_error(E_COMPILE_ERROR, "Declaration of %s must be compatible with %s",
								zend_get_function_declaration(fn TSRMLS_CC),
								zend_get_function_declaration(existing_fn TSRMLS_CC));
						}
						return;
					}
				}
			} else {
				ALLOC_HASHTABLE(*overriden);
				zend_hash_init_ex(*overriden, 2, NULL, NULL, 0, 0);
			}
			zend_hash_quick_update(*overriden, arKey, nKeyLength, h, fn, sizeof(zend_function), (void**)&fn);
			return;
		} else if (existing_fn->common.fn_flags & ZEND_ACC_ABSTRACT) {

			if (!zend_traits_method_compatibility_check(fn, existing_fn TSRMLS_CC)) {
				zend_error(E_COMPILE_ERROR, "Declaration of %s must be compatible with %s",
					zend_get_function_declaration(fn TSRMLS_CC),
					zend_get_function_declaration(existing_fn TSRMLS_CC));
			}
		} else if (fn->common.fn_flags & ZEND_ACC_ABSTRACT) {

			if (!zend_traits_method_compatibility_check(existing_fn, fn TSRMLS_CC)) {
				zend_error(E_COMPILE_ERROR, "Declaration of %s must be compatible with %s",
					zend_get_function_declaration(fn TSRMLS_CC),
					zend_get_function_declaration(existing_fn TSRMLS_CC));
			}
			return;
		} else if ((existing_fn->common.scope->ce_flags & ZEND_ACC_TRAIT) == ZEND_ACC_TRAIT) {

#if 1
			zend_error(E_COMPILE_ERROR, "Trait method %s has not been applied, because there are collisions with other trait methods on %s",
				name, ce->name);
#else
			zend_error(E_COMPILE_ERROR, "Trait method %s::%s has not been applied as %s::%s, because of collision with %s::%s",
				fn->common.scope->name, fn->common.function_name,
				ce->name, name,
				existing_fn->common.scope->name, existing_fn->common.function_name);
#endif
		} else {


			do_inheritance_check_on_method(fn, existing_fn TSRMLS_CC);
		}
	}

	function_add_ref(fn);
	zend_hash_quick_update(&ce->function_table, arKey, nKeyLength, h, fn, sizeof(zend_function), (void**)&fn);
	zend_add_magic_methods(ce, arKey, nKeyLength, fn TSRMLS_CC);
}
