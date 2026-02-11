info_func(struct cmdsocket *cmdsocket, struct command *command, const char *params)
{
	char addr[INET6_ADDRSTRLEN];
	const char *addr_start;

	INFO_OUT("%s %s\n", command->name, params);

	addr_start = inet_ntop(cmdsocket->addr.sin6_family, &cmdsocket->addr.sin6_addr, addr, sizeof(addr));
	if(!strncmp(addr, "::ffff:", 7) && strchr(addr, '.') != NULL) {
		addr_start += 7;
	}

	evbuffer_add_printf(
			cmdsocket->buffer,
			"Client address: %s\nClient port: %hu\n",
			addr_start,
			cmdsocket->addr.sin6_port
			);
}
