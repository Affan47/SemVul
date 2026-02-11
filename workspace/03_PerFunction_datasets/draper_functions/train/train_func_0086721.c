set_socket_ttl(ioa_socket_handle s, int ttl)
{
	if(s->default_ttl < 0)
		return -1;

	if(ttl < 0)
		ttl = s->default_ttl;

	CORRECT_RAW_TTL(ttl);

	if(ttl > s->default_ttl)
		ttl=s->default_ttl;

	if(s->current_ttl != ttl) {
		int ret = set_raw_socket_ttl(s->fd, s->family, ttl);
		s->current_ttl = ttl;
		return ret;
	}

	return 0;
}
