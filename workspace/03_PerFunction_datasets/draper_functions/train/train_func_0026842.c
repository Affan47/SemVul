sxe_object_clone(void *object, void **clone_ptr TSRMLS_DC)
{
	php_sxe_object *sxe = (php_sxe_object *) object;
	php_sxe_object *clone;
	xmlNodePtr nodep = NULL;
	xmlDocPtr docp = NULL;

	clone = php_sxe_object_new(sxe->zo.ce TSRMLS_CC);
	clone->document = sxe->document;
	if (clone->document) {
		clone->document->refcount++;
		docp = clone->document->ptr;
	}

	clone->iter.isprefix = sxe->iter.isprefix;
	if (sxe->iter.name != NULL) {
		clone->iter.name = xmlStrdup((xmlChar *)sxe->iter.name);
	}
	if (sxe->iter.nsprefix != NULL) {
		clone->iter.nsprefix = xmlStrdup((xmlChar *)sxe->iter.nsprefix);
	}
	clone->iter.type = sxe->iter.type;

	if (sxe->node) {
		nodep = xmlDocCopyNode(sxe->node->node, docp, 1);
	}

	php_libxml_increment_node_ptr((php_libxml_node_object *)clone, nodep, NULL TSRMLS_CC);

	*clone_ptr = (void *) clone;
}
