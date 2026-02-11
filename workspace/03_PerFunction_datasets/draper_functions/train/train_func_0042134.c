print_endpoint_stat(struct htc_target *target, char *buf,
					unsigned int buf_len, unsigned int len,
					int offset, const char *name)
{
	int i;
	struct htc_endpoint_stats *ep_st;
	u32 *counter;

	len += scnprintf(buf + len, buf_len - len, "%s:", name);
	for (i = 0; i < ENDPOINT_MAX; i++) {
		ep_st = &target->endpoint[i].ep_st;
		counter = ((u32 *) ep_st) + (offset / 4);
		len += scnprintf(buf + len, buf_len - len, " %u", *counter);
	}
	len += scnprintf(buf + len, buf_len - len, "\n");

	return len;
}
