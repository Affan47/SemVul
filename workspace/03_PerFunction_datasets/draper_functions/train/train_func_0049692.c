dom_xpath_document_read(dom_object *obj, zval **retval TSRMLS_DC)
{
	xmlDoc *docp = NULL;
	xmlXPathContextPtr ctx;
	int ret;

	ctx = (xmlXPathContextPtr) obj->ptr;

	if (ctx) {
		docp = (xmlDocPtr) ctx->doc;
	}

	ALLOC_ZVAL(*retval);
	if (NULL == (*retval = php_dom_create_object((xmlNodePtr) docp, &ret, NULL, *retval, obj TSRMLS_CC))) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Cannot create required DOM object");
		return FAILURE;
	}
	return SUCCESS;
}
