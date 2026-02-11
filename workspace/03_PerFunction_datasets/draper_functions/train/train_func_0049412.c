psock_local(int iface, struct psock * s, uint8_t flags)
{
	memset(s, 0, sizeof *s);
	if (iface >= nr_iface) {
		err("psock_local: Invalid interface number %d\n", iface);
		return NULL;
	}
	s->hiface = h_iface[iface];
	s->flags = flags | PS_FLAG_LOCAL;
	s->valid = PS_VALID;
	return s;
}
