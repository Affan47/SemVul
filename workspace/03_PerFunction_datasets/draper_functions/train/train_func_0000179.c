wi_ip_version(wi_string_t *ip) {
	struct sockaddr_in		sa_in;
	struct sockaddr_in6		sa_in6;

	if(wi_string_contains_string(ip, WI_STR("."), 0)) {
		if(inet_pton(AF_INET, wi_string_cstring(ip), &sa_in.sin_addr) > 0)
			return WI_IP_IPV4;
	}
	else if(wi_string_contains_string(ip, WI_STR(":"), 0)) {
		if(inet_pton(AF_INET6, wi_string_cstring(ip), &sa_in6.sin6_addr) > 0)
			return WI_IP_IPV6;
	}

	return WI_IP_NULL;
}
