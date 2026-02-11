dump() const {
	std::clog << "Dumping parsed whitelist:" << std::endl;
	for (std::list<std::pair<struct ::in6_addr, int> >::const_iterator p = whitelisted_addresses.begin(); p!= whitelisted_addresses.end(); ++p) {
	    char address[INET6_ADDRSTRLEN];

	    ::inet_ntop(AF_INET6, &(p->first), address, sizeof(address));

	    std::clog << address << "/" << (p->second) << std::endl;
	}

	std::clog << "***** END *****" << std::endl;
    }
