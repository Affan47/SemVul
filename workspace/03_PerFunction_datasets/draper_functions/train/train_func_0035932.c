isns_attr_type_opaque_compare(const isns_value_t *a, const isns_value_t *b)
{
	long	delta;

	delta = a->iv_opaque.len - b->iv_opaque.len;
	if (delta)
		return delta;

	return memcmp(a->iv_opaque.ptr, b->iv_opaque.ptr, a->iv_opaque.len);
}
