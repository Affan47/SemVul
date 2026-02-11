read_new_length (const guchar **at,
                 const guchar *end,
                 gsize *pkt_len)
{
	guint8 c, c1;
	guint32 val;

	if (!read_byte (at, end, &c))
		return FALSE;
	if (c < 192) {
		*pkt_len = c;
	} else if (c >= 192 && c <= 223) {
		if (!read_byte (at, end, &c1))
			return FALSE;
		*pkt_len = ((c - 192) << 8) + c1 + 192;
	} else if (c == 255) {
		if (!read_uint32 (at, end, &val))
			return FALSE;
		*pkt_len = val;
	} else {

		return FALSE;
	}

	return TRUE;
}
