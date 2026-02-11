isns_attr_print_value(const isns_attr_t *attr, char *buffer, size_t size)
{
	const isns_tag_type_t *tag_type = attr->ia_tag;
	const isns_attr_type_t *type = attr->ia_value.iv_type;

	if (tag_type->it_print && type == tag_type->it_type)
		tag_type->it_print(&attr->ia_value, buffer, size);
	else
		type->it_print(&attr->ia_value, buffer, size);
	return buffer;
}
