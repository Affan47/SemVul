isns_attr_type_uint32_encode(buf_t *bp, const isns_value_t *value)
{
	return buf_put32(bp, 4) && buf_put32(bp, value->iv_uint32);
}
