dump_local(ostream &os)
{
	if (mode != AA_VALID_NET_PERMS) {
		os << " (";

		if (mode & AA_NET_SEND)
			os << "send ";
		if (mode & AA_NET_RECEIVE)
			os << "receive ";
		if (mode & AA_NET_CREATE)
			os << "create ";
		if (mode & AA_NET_SHUTDOWN)
			os << "shutdown ";
		if (mode & AA_NET_CONNECT)
			os << "connect ";
		if (mode & AA_NET_SETATTR)
			os << "setattr ";
		if (mode & AA_NET_GETATTR)
			os << "getattr ";
		if (mode & AA_NET_BIND)
			os << "bind ";
		if (mode & AA_NET_ACCEPT)
			os << "accept ";
		if (mode & AA_NET_LISTEN)
			os << "listen ";
		if (mode & AA_NET_SETOPT)
			os << "setopt ";
		if (mode & AA_NET_GETOPT)
			os << "getopt ";
		os << ")";
	}

	if (sock_type)
		os << " type=" << sock_type;
	if (proto)
		os << " protocol=" << proto;
	return os;
}
