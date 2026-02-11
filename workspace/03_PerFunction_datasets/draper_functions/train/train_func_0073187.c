isns_object_get_key_attrs(isns_object_t *obj,
			isns_attr_list_t *result)
{
	isns_object_template_t *tmpl = obj->ie_template;
	isns_attr_list_t *attrs = &obj->ie_attrs;
	isns_attr_t	*attr;
	unsigned int	i;

	for (i = 0; i < tmpl->iot_num_keys; ++i) {
		uint32_t	tag = tmpl->iot_keys[i];

		if (!isns_attr_list_get_attr(attrs, tag, &attr)) {
			isns_error("%s: %s object is missing key attr %u\n",
					__FUNCTION__,
					tmpl->iot_name,
					tag);
			return 0;
		}
		isns_attr_list_append_attr(result, attr);
	}
	return 1;
}
