zend_destroy_property_info(zend_property_info *property_info)
{
	str_efree(property_info->name);
	if (property_info->doc_comment) {
		efree((char*)property_info->doc_comment);
	}
}
