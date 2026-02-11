byte_array_append(bytearray_t *ba, void *buf, size_t len)
{
	if (!ba || !ba->data || (len <= 0)) return;
	size_t remaining = ba->capacity-ba->len;
	if (len > remaining) {
		ba->data = realloc(ba->data, ba->capacity + (len - remaining));
		ba->capacity += (len - remaining);
	}
	memcpy(ba->data+ba->len, buf, len);
	ba->len += len;
}
