get_addr(inet_prefix *dst, char *arg, int family)
{
	if (family == AF_PACKET) {
		bb_error_msg_and_die("\"%s\" may be inet %s, but it is not allowed in this context", arg, "address");
	}
	if (get_addr_1(dst, arg, family)) {
		bb_error_msg_and_die("an %s %s is expected rather than \"%s\"", "inet", "address", arg);
	}
	return 0;
}
