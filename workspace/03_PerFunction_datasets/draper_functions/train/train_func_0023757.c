add_ns(const string &host, const string &port = "53")
{
	err = "";
	struct addrinfo *ai = NULL, hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = SOCK_DGRAM;

 	int e;
	if ((e = getaddrinfo(host.c_str(), port.c_str(), &hints, &ai)) < 0) {
		err = "DNS::add_ns:getaddrinfo:";
		err += gai_strerror(e);
		return -1;
	}

	ns_map[*(ai->ai_addr)] = ai->ai_addrlen;
	freeaddrinfo(ai);
	return 0;
}
