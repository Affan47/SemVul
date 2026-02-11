php_set_attribute_id(xmlAttrPtr attrp, zend_bool is_id)
{
	if (is_id == 1 && attrp->atype != XML_ATTRIBUTE_ID) {
		xmlChar *id_val;

		id_val = xmlNodeListGetString(attrp->doc, attrp->children, 1);
		if (id_val != NULL) {
			xmlAddID(NULL, attrp->doc, id_val, attrp);
			xmlFree(id_val);
		}
	} else {
		if (attrp->atype == XML_ATTRIBUTE_ID) {
			xmlRemoveID(attrp->doc, attrp);
			attrp->atype = 0;
		}
	}
}
