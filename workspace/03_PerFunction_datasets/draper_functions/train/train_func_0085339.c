GF_IPMPX_GetByteArraySize(GF_IPMPX_ByteArray *ba)
{
	if (!ba) return 1;
	return ba->length + get_field_size(ba->length);
}
