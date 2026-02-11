zend_destroy_property_info_internal(zend_property_info *property_info)
{
	str_free((char*)property_info->name);
}
