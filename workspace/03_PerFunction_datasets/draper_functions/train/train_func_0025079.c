__isns_object_translate_attr(isns_object_t *obj,
		uint32_t old_tag, uint32_t new_tag,
		isns_attr_list_t *dst)
{
	isns_value_t	value;

	if (!isns_attr_list_get_value(&obj->ie_attrs, old_tag, &value))
		return 0;
	isns_attr_list_append_value(dst, new_tag, NULL, &value);
	return 1;
}
