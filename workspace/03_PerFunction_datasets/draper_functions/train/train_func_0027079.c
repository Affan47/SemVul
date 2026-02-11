sock_eq(struct sockaddr_in6 *a1, struct sockaddr_in6 *a2) {
	if (a1->sin6_family == a2->sin6_family) {
		if (a1->sin6_family == AF_INET)
			return ((((struct sockaddr_in *)a1)->sin_port ==
				 ((struct sockaddr_in *)a2)->sin_port) &&
				(((struct sockaddr_in *)a1)->sin_addr.s_addr ==
				 ((struct sockaddr_in *)a2)->sin_addr.s_addr));
		else
			return ((a1->sin6_port == a2->sin6_port) &&
				!memcmp(&a1->sin6_addr, &a2->sin6_addr,
					sizeof (struct in6_addr)));
	}
	if (a1->sin6_family == AF_INET) {
		struct sockaddr_in6 *sap = a1;
		a1 = a2;
		a2 = sap;
	}
	return ((a1->sin6_port == ((struct sockaddr_in *)a2)->sin_port) &&
		IN6_IS_ADDR_V4MAPPED(&a1->sin6_addr) &&
		(a1->sin6_addr.s6_addr32[3] ==
		 ((struct sockaddr_in *)a2)->sin_addr.s_addr));
}
