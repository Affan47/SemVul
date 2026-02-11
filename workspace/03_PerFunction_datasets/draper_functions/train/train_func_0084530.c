php_dom_create_object(xmlNodePtr obj, int *found, zval *wrapper_in, zval *return_value, dom_object *domobj TSRMLS_DC)
{
	zval *wrapper;
	zend_class_entry *ce;
	dom_object *intern;

	*found = 0;

	if (!obj) {
		ALLOC_ZVAL(wrapper);
		ZVAL_NULL(wrapper);
		return wrapper;
	}

	if ((intern = (dom_object *) php_dom_object_get_data((void *) obj))) {
		return_value->type = IS_OBJECT;
		Z_SET_ISREF_P(return_value);
		return_value->value.obj.handle = intern->handle;
		return_value->value.obj.handlers = dom_get_obj_handlers(TSRMLS_C);
		zval_copy_ctor(return_value);
		*found = 1;
		return return_value;
	}

	wrapper = return_value;

	switch (obj->type) {
		case XML_DOCUMENT_NODE:
		case XML_HTML_DOCUMENT_NODE:
		{
			ce = dom_document_class_entry;
			break;
		}
		case XML_DTD_NODE:
		case XML_DOCUMENT_TYPE_NODE:
		{
			ce = dom_documenttype_class_entry;
			break;
		}
		case XML_ELEMENT_NODE:
		{
			ce = dom_element_class_entry;
			break;
		}
		case XML_ATTRIBUTE_NODE:
		{
			ce = dom_attr_class_entry;
			break;
		}
		case XML_TEXT_NODE:
		{
			ce = dom_text_class_entry;
			break;
		}
		case XML_COMMENT_NODE:
		{
			ce = dom_comment_class_entry;
			break;
		}
		case XML_PI_NODE:
		{
			ce = dom_processinginstruction_class_entry;
			break;
		}
		case XML_ENTITY_REF_NODE:
		{
			ce = dom_entityreference_class_entry;
			break;
		}
		case XML_ENTITY_DECL:
		case XML_ELEMENT_DECL:
		{
			ce = dom_entity_class_entry;
			break;
		}
		case XML_CDATA_SECTION_NODE:
		{
			ce = dom_cdatasection_class_entry;
			break;
		}
		case XML_DOCUMENT_FRAG_NODE:
		{
			ce = dom_documentfragment_class_entry;
			break;
		}
		case XML_NOTATION_NODE:
		{
			ce = dom_notation_class_entry;
			break;
		}
		case XML_NAMESPACE_DECL:
		{
			ce = dom_namespace_node_class_entry;
			break;
		}
		default:
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unsupported node type: %d", Z_TYPE_P(obj));
			ZVAL_NULL(wrapper);
			return wrapper;
	}

	if (domobj && domobj->document) {
		ce = dom_get_doc_classmap(domobj->document, ce TSRMLS_CC);
	}
	object_init_ex(wrapper, ce);

	intern = (dom_object *)zend_objects_get_address(wrapper TSRMLS_CC);
	if (obj->doc != NULL) {
		if (domobj != NULL) {
			intern->document = domobj->document;
		}
		php_libxml_increment_doc_ref((php_libxml_node_object *)intern, obj->doc TSRMLS_CC);
	}

	php_libxml_increment_node_ptr((php_libxml_node_object *)intern, obj, (void *)intern TSRMLS_CC);
	return (wrapper);
}
