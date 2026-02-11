isns_attr_match(const isns_attr_t *a, const isns_attr_t *b)
{
	const isns_attr_type_t *type;

	if (a->ia_tag_id != b->ia_tag_id)
		return 0;


	if (a->ia_value.iv_type == &isns_attr_type_nil
	 || b->ia_value.iv_type == &isns_attr_type_nil)
		return 1;

	if (a->ia_value.iv_type != b->ia_value.iv_type)
		return 0;
	type = a->ia_value.iv_type;

	if (type->it_match)
		return type->it_match(&a->ia_value, &b->ia_value);

	return !memcmp(&a->ia_value, &b->ia_value, sizeof(isns_value_t));
}
