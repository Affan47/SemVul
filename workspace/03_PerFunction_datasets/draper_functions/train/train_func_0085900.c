short_byte_size_to_buf(uint64 size, bool metric, char *buf, size_t buflen)
{
	size_t w;

	if (size < kilo(metric)) {
		uint n = size;
		w = str_bprintf(buf, buflen, "%u B", n);
	} else {
		uint q, r;
		char c;

		c = norm_size_scale(size, &q, &r, metric);
		r = (r * 100) / kilo(metric);
		w = str_bprintf(buf, buflen,
				"%u.%02u %c%s", q, r, c, byte_suffix(metric));
	}

	return w;
}
