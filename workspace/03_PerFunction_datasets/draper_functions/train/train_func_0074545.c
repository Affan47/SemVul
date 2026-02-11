sxe_property_get_adr(zval *object, zval *member TSRMLS_DC)
{
	php_sxe_object *sxe;
	xmlNodePtr      node;
	zval           *return_value;
	char           *name;
	SXE_ITER        type;

	sxe = php_sxe_fetch_object(object TSRMLS_CC);

	GET_NODE(sxe, node);
	convert_to_string(member);
	name = Z_STRVAL_P(member);
	node = sxe_get_element_by_name(sxe, node, &name, &type TSRMLS_CC);
	if (node) {
		return NULL;
	}
	if (sxe_prop_dim_write(object, member, NULL, 1, 0, &node TSRMLS_CC) != SUCCESS) {
		return NULL;
	}
	type = SXE_ITER_NONE;
	name = NULL;

	MAKE_STD_ZVAL(return_value);
	_node_as_zval(sxe, node, return_value, type, name, sxe->iter.nsprefix, sxe->iter.isprefix TSRMLS_CC);

	sxe = php_sxe_fetch_object(return_value TSRMLS_CC);
	if (sxe->tmp) {
		zval_ptr_dtor(&sxe->tmp);
	}
	sxe->tmp = return_value;
	Z_SET_ISREF_P(return_value);

	return &sxe->tmp;
}
