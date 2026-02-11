dom_characterdata_length_read(dom_object *obj, zval **retval TSRMLS_DC)
{
	xmlNodePtr nodep;
	xmlChar *content;
	long length = 0;

	nodep = dom_object_get_node(obj);

	if (nodep == NULL) {
		php_dom_throw_error(INVALID_STATE_ERR, 0 TSRMLS_CC);
		return FAILURE;
	}

	ALLOC_ZVAL(*retval);

	content = xmlNodeGetContent(nodep);

	if (content) {
		length = xmlUTF8Strlen(content);
		xmlFree(content);
	}

	ZVAL_LONG(*retval, length);

	return SUCCESS;
}
