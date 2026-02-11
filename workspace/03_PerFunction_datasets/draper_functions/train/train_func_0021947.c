zend_duplicate_property_info(zend_property_info *property_info)
{
	if (!IS_INTERNED(property_info->name)) {
		property_info->name = estrndup(property_info->name, property_info->name_length);
	}
	if (property_info->doc_comment) {
		property_info->doc_comment = estrndup(property_info->doc_comment, property_info->doc_comment_len);
	}
}
