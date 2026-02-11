isns_object_extract_writable(const isns_object_t *obj,
		isns_attr_list_t *list)
{
	const isns_attr_list_t *src = &obj->ie_attrs;
	unsigned int	i;

	for (i = 0; i < src->ial_count; ++i) {
		isns_attr_t	*attr = src->ial_data[i];

		if (attr->ia_tag->it_readonly)
			continue;
		isns_attr_list_append_attr(list, attr);
	}

	return 1;
}
