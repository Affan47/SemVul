zend_reflection_class_factory(zend_class_entry *ce, zval *object TSRMLS_DC)
{
	reflection_object *intern;
	zval *name;

	MAKE_STD_ZVAL(name);
	ZVAL_STRINGL(name, ce->name, ce->name_length, 1);
	reflection_instantiate(reflection_class_ptr, object TSRMLS_CC);
	intern = (reflection_object *) zend_object_store_get_object(object TSRMLS_CC);
	intern->ptr = ce;
	intern->ref_type = REF_TYPE_OTHER;
	intern->ce = ce;
	reflection_update_property(object, "name", name);
}
