extended_attrlen(const uint8_t *start, const uint8_t *end)
{
	ssize_t total;
	const uint8_t *data = start;

	if ((data[3] & 0x80) == 0) return 0;
	total = data[1] - 4;
	data += data[1];

	while (data < end) {
		if ((data + 4) > end) return -1;

		if ((data[0] != start[0]) ||
		    (data[1] < 4) ||
		    (data[2] != start[2])) return -1;

		total += data[1] - 4;
		if ((data[3] & 0x80) == 0) break;
		data += data[1];
	}

	return total;
}
