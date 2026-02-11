host_addr_teredo_client(const host_addr_t from, host_addr_t *to)
{
	if (host_addr_is_teredo(from)) {
		if (to) {
			*to = host_addr_get_ipv4(host_addr_teredo_client_ipv4(from));
		}
		return TRUE;
	} else {
		if (to) {
			*to = zero_host_addr;
		}
		return FALSE;
	}
}
