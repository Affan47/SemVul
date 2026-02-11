bind_ioa_socket(ioa_socket_handle s, const ioa_addr* local_addr, int reusable)
{
	if(!s || (s->parent_s))
		return 0;

	if (s && s->fd >= 0 && s->e && local_addr) {

		int res = addr_bind(s->fd, local_addr, reusable);
		if (res >= 0) {
			s->bound = 1;
			addr_cpy(&(s->local_addr), local_addr);
			if(addr_get_port(local_addr)<1) {
				ioa_addr tmpaddr;
				addr_get_from_sock(s->fd, &tmpaddr);
				if(addr_any(&(s->local_addr))) {
					addr_cpy(&(s->local_addr),&tmpaddr);
				} else {
					addr_set_port(&(s->local_addr),addr_get_port(&tmpaddr));
				}
			}
			s->local_addr_known = 1;
			return 0;
		}
	}
	return -1;
}
