suggested_script(resource_t *res, unsigned int class)
{
	int offset;
	if (!res || class >= res->size >> 2)
		return -1;

	offset = 2 + (class << 2);

	return getInt16(res->data + offset);
}
