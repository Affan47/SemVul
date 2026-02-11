get_associated_ips(const struct lease *lease,
		   struct lease *(*next)(const struct lease *),
		   const struct lease *newest,
		   u_int32_t *associated_ips,
		   unsigned int associated_ips_size) {

	const struct lease *p;
	int cnt;


	if (lease == NULL) {
		return 0;
	}

	cnt = 0;
	for (p=lease; p != NULL; p=next(p)) {
		if ((p->binding_state == FTS_ACTIVE) && (p != newest)) {
			if (cnt < associated_ips_size) {
				memcpy(&associated_ips[cnt],
				       p->ip_addr.iabuf,
				       sizeof(associated_ips[cnt]));
			}
			cnt++;
		}
	}
	return cnt;
}
