istgt_iscsi_append_text(CONN_Ptr conn, const char *key, const char *val, uint8_t *data, int alloc_len, int data_len)
{
	int total;
	int len;

	total = data_len;
	if (alloc_len < 1) {
		return 0;
	}
	if (total > alloc_len) {
		total = alloc_len;
		data[total - 1] = '\0';
		return total;
	}

	if (alloc_len - total < 1) {
		ISTGT_ERRLOG("data space small %d\n", alloc_len);
		return total;
	}
	len = snprintf((char *) data + total, alloc_len - total, "%s=%s",
	    key, val);
	total += len + 1;

	return total;
}
