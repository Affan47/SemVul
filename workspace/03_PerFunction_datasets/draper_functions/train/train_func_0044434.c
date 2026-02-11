apol_str_to_protocol(const char *protocol_str)
{
	if (protocol_str == NULL) {
		errno = EINVAL;
		return 0;
	}
	if (strcmp(protocol_str, "tcp") == 0 || strcmp(protocol_str, "TCP") == 0) {
		return IPPROTO_TCP;
	}
	if (strcmp(protocol_str, "udp") == 0 || strcmp(protocol_str, "UDP") == 0) {
		return IPPROTO_UDP;
	}
	errno = EPROTONOSUPPORT;
	return 0;
}
