fill_key(char *buf, size_t len, long i)
{
	size_t w;
	size_t offset = 0;
	size_t avail = len;

	if (common_head_tail) {
		g_assert(len > COMMON_HEAD_TAIL);
		memset(buf, 0, COMMON_HEAD_TAIL);
		offset = COMMON_HEAD_TAIL;
		avail -= COMMON_HEAD_TAIL;
	}

	if (randomize) {
		int v = rand31();
		w = str_bprintf(&buf[offset], avail, "%06d%010ld", v, i);
	} else {
		w = str_bprintf(&buf[offset], avail, "%016ld", i);
	}
	if (large_keys) {
		size_t off = len - LARGE_KEY_TAIL;
		memset(&buf[w+offset], 0, len - w);
		g_assert(avail > LARGE_KEY_TAIL + COMMON_HEAD_TAIL);
		if (common_head_tail)
			off -= COMMON_HEAD_TAIL;
		str_bprintf(&buf[off], LARGE_KEY_TAIL, "%016ld", i);
	}
}
