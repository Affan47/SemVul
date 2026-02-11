reflection_extension_factory(zval *object, const char *name_str TSRMLS_DC)
{
	reflection_object *intern;
	zval *name;
	int name_len = strlen(name_str);
	char *lcname;
	struct _zend_module_entry *module;
	ALLOCA_FLAG(use_heap)

	lcname = do_alloca(name_len + 1, use_heap);
	zend_str_tolower_copy(lcname, name_str, name_len);
	if (zend_hash_find(&module_registry, lcname, name_len + 1, (void **)&module) == FAILURE) {
		free_alloca(lcname, use_heap);
		return;
	}
	free_alloca(lcname, use_heap);

	reflection_instantiate(reflection_extension_ptr, object TSRMLS_CC);
	intern = (reflection_object *) zend_object_store_get_object(object TSRMLS_CC);
	MAKE_STD_ZVAL(name);
	ZVAL_STRINGL(name, module->name, name_len, 1);
	intern->ptr = module;
	intern->ref_type = REF_TYPE_OTHER;
	intern->ce = NULL;
	zend_hash_update(Z_OBJPROP_P(object), "name", sizeof("name"), (void **) &name, sizeof(zval *), NULL);
}
