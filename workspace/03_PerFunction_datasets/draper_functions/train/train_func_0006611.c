sprint_u32_handle(__u32 handle, char *buf)
{
	int bsize = SPRINT_BSIZE-1;
	__u32 htid = TC_U32_HTID(handle);
	__u32 hash = TC_U32_HASH(handle);
	__u32 nodeid = TC_U32_NODE(handle);
	char *b = buf;

	if (handle == 0) {
		snprintf(b, bsize, "none");
		return b;
	}
	if (htid) {
		int l = snprintf(b, bsize, "%x:", htid>>20);
		bsize -= l;
		b += l;
	}
	if (nodeid|hash) {
		if (hash) {
			int l = snprintf(b, bsize, "%x", hash);
			bsize -= l;
			b += l;
		}
		if (nodeid) {
			int l = snprintf(b, bsize, ":%x", nodeid);
			bsize -= l;
			b += l;
		}
	}
	if (show_raw)
		snprintf(b, bsize, "[%08x] ", handle);
	return buf;
}
