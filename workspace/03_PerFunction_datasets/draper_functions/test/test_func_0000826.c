__isns_attr_set_value(isns_attr_t *attr, const isns_value_t *new_value)
{
	const isns_attr_type_t *type, *old_type;
	isns_value_t *old_value;

	old_value = &attr->ia_value;
	if (old_value == new_value)
		return;

	old_type = old_value->iv_type;
	if (old_type && old_type->it_destroy)
		old_type->it_destroy(old_value);

	if (!new_value || !(type = new_value->iv_type))
		type = attr->ia_tag->it_type;


	if (new_value) {
		if (type->it_assign) {
			type->it_assign(&attr->ia_value, new_value);
		} else {
			attr->ia_value = *new_value;
		}
	}
	attr->ia_value.iv_type = type;
}
