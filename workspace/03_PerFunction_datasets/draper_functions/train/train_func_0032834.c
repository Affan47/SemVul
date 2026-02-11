zend_add_trait_alias(znode *method_reference, znode *modifiers, znode *alias TSRMLS_DC)
{
	zend_class_entry *ce = CG(active_class_entry);
	zend_trait_alias *trait_alias;

	if (Z_LVAL(modifiers->u.constant) == ZEND_ACC_STATIC) {
		zend_error(E_COMPILE_ERROR, "Cannot use 'static' as method modifier");
		return;
	} else if (Z_LVAL(modifiers->u.constant) == ZEND_ACC_ABSTRACT) {
		zend_error(E_COMPILE_ERROR, "Cannot use 'abstract' as method modifier");
		return;
	} else if (Z_LVAL(modifiers->u.constant) == ZEND_ACC_FINAL) {
		zend_error(E_COMPILE_ERROR, "Cannot use 'final' as method modifier");
		return;
	}

	trait_alias = emalloc(sizeof(zend_trait_alias));
	trait_alias->trait_method = (zend_trait_method_reference*)method_reference->u.op.ptr;
	trait_alias->modifiers = Z_LVAL(modifiers->u.constant);
	if (alias) {
		trait_alias->alias = Z_STRVAL(alias->u.constant);
		trait_alias->alias_len = Z_STRLEN(alias->u.constant);
	} else {
		trait_alias->alias = NULL;
	}
	trait_alias->function = NULL;

	zend_add_to_list(&ce->trait_aliases, trait_alias TSRMLS_CC);
}
