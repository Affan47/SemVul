isns_object_prune_attrs(isns_object_t *obj)
{
	isns_object_template_t *tmpl = obj->ie_template;
	uint32_t	tags[16];
	unsigned int	i;

	isns_assert(tmpl->iot_num_keys + 1 <= 16);
	for (i = 0; i < tmpl->iot_num_keys; ++i)
		tags[i] = tmpl->iot_keys[i];
	if (tmpl->iot_index)
		tags[i++] = tmpl->iot_index;
	isns_attr_list_prune(&obj->ie_attrs, tags, i);
}
