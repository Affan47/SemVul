php_sxe_count_elements_helper(php_sxe_object *sxe, long *count TSRMLS_DC)
{
	xmlNodePtr       node;
	zval            *data;

	*count = 0;

	data = sxe->iter.data;
	sxe->iter.data = NULL;

	node = php_sxe_reset_iterator(sxe, 0 TSRMLS_CC);

	while (node)
	{
		(*count)++;
		node = php_sxe_iterator_fetch(sxe, node->next, 0 TSRMLS_CC);
	}

	if (sxe->iter.data) {
		zval_ptr_dtor(&sxe->iter.data);
	}
	sxe->iter.data = data;

	return SUCCESS;
}
