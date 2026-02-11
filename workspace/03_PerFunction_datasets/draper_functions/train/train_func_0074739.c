php_sxe_get_iterator(zend_class_entry *ce, zval *object, int by_ref TSRMLS_DC)
{
	php_sxe_iterator *iterator;

	if (by_ref) {
		zend_error(E_ERROR, "An iterator cannot be used with foreach by reference");
	}
	iterator = emalloc(sizeof(php_sxe_iterator));

	object->refcount++;
	iterator->intern.data = (void*)object;
	iterator->intern.funcs = &php_sxe_iterator_funcs;
	iterator->sxe = php_sxe_fetch_object(object TSRMLS_CC);

	return (zend_object_iterator*)iterator;
}
