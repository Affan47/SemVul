create_addr(const char *buffer, isc_netaddr_t *addr, int convert_zero) {
	struct in_addr v4;
	struct in6_addr v6;

	if (inet_aton(buffer, &v4) == 1) {
		if (convert_zero) {
			unsigned char zeroaddress[] = {0, 0, 0, 0};
			unsigned char loopaddress[] = {127, 0, 0, 1};
			if (memcmp(&v4, zeroaddress, 4) == 0)
				memmove(&v4, loopaddress, 4);
		}
		addr->family = AF_INET;
		memmove(&addr->type.in, &v4, NS_INADDRSZ);
		addr->zone = 0;
	} else if (inet_pton(AF_INET6, buffer, &v6) == 1) {
		addr->family = AF_INET6;
		memmove(&addr->type.in6, &v6, NS_IN6ADDRSZ);
		addr->zone = 0;
	} else
		return (ISC_R_BADADDRESSFORM);

	return (ISC_R_SUCCESS);
}
