php_sxe_get_first_node(php_sxe_object *sxe, xmlNodePtr node TSRMLS_DC)
{
	php_sxe_object *intern;
	xmlNodePtr retnode = NULL;

	if (sxe && sxe->iter.type != SXE_ITER_NONE) {
		php_sxe_reset_iterator(sxe, 1 TSRMLS_CC);
		if (sxe->iter.data) {
			intern = (php_sxe_object *)zend_object_store_get_object(sxe->iter.data TSRMLS_CC);
			GET_NODE(intern, retnode)
		}
		return retnode;
	} else {
		return node;
	}
}
