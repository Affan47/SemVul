i2400m_tlv_buffer_walk(
	struct i2400m *i2400m,
	const void *tlv_buf, size_t buf_size,
	const struct i2400m_tlv_hdr *tlv_pos)
{
	struct device *dev = i2400m_dev(i2400m);
	const struct i2400m_tlv_hdr *tlv_top = tlv_buf + buf_size;
	size_t offset, length, avail_size;
	unsigned type;

	if (tlv_pos == NULL)
		tlv_pos = tlv_buf;
	else
		tlv_pos = (void *) tlv_pos
			+ le16_to_cpu(tlv_pos->length) + sizeof(*tlv_pos);
	if (tlv_pos == tlv_top) {
		tlv_pos = NULL;
		goto error_beyond_end;
	}
	if (tlv_pos > tlv_top) {
		tlv_pos = NULL;
		WARN_ON(1);
		goto error_beyond_end;
	}
	offset = (void *) tlv_pos - (void *) tlv_buf;
	avail_size = buf_size - offset;
	if (avail_size < sizeof(*tlv_pos)) {
		dev_err(dev, "HW BUG? tlv_buf %p [%zu bytes], tlv @%zu: "
			"short header\n", tlv_buf, buf_size, offset);
		goto error_short_header;
	}
	type = le16_to_cpu(tlv_pos->type);
	length = le16_to_cpu(tlv_pos->length);
	if (avail_size < sizeof(*tlv_pos) + length) {
		dev_err(dev, "HW BUG? tlv_buf %p [%zu bytes], "
			"tlv type 0x%04x @%zu: "
			"short data (%zu bytes vs %zu needed)\n",
			tlv_buf, buf_size, type, offset, avail_size,
			sizeof(*tlv_pos) + length);
		goto error_short_header;
	}
error_short_header:
error_beyond_end:
	return tlv_pos;
}
