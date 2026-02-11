xmmsv_get_uint (const xmmsv_t *val, uint32_t *r)
{
	if (!val)
		return 0;
	if (val->type != XMMSV_TYPE_INT32)
		return 0;

	*r = val->value.int32;

	return 1;
}
