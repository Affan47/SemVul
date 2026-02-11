socket_connection_allowed(const host_addr_t addr, enum socket_type type)
{
	unsigned flag = 0;

	if (hostiles_is_bad(addr)) {
		if (GNET_PROPERTY(socket_debug)) {
			hostiles_flags_t flags = hostiles_check(addr);
			g_warning("not connecting [%s] to hostile host %s (%s)",
				socket_type_to_string(type), host_addr_to_string(addr),
				hostiles_flags_to_string(flags));
		}
		errno = EPERM;
		return -1;
	}

	switch (type) {
	case SOCK_TYPE_DOWNLOAD:	flag = CTL_D_OUTGOING; break;
	case SOCK_TYPE_HTTP:		flag = CTL_D_OUTGOING; break;
	case SOCK_TYPE_CONTROL:		flag = CTL_D_GNUTELLA; break;
	case SOCK_TYPE_UPLOAD:		flag = CTL_D_INCOMING; break;
	case SOCK_TYPE_CONNBACK:
		flag = ctl_limit(addr, CTL_D_STEALTH) ? CTL_D_GNUTELLA : 0;
		break;
	default:
		g_warning("socket_connect_prepare(): unexpected type \"%s\"",
			socket_type_to_string(type));
		flag = CTL_D_OUTGOING;
		break;
	}

	if (ctl_limit(addr, flag)) {
		if (GNET_PROPERTY(socket_debug) || GNET_PROPERTY(ctl_debug)) {
			g_warning("CTL not connecting [%s] to host %s [%s]",
				socket_type_to_string(type), host_addr_to_string(addr),
				gip_country_cc(addr));
		}
		errno = EPERM;
		return -1;
	}

	return 0;
}
