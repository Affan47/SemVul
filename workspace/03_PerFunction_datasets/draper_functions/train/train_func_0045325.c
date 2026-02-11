isc_sockaddr_issitelocal(const isc_sockaddr_t *sockaddr) {
	isc_netaddr_t netaddr;

	if (sockaddr->type.sa.sa_family == AF_INET6) {
		isc_netaddr_fromsockaddr(&netaddr, sockaddr);
		return (isc_netaddr_issitelocal(&netaddr));
	}
	return (ISC_FALSE);
}
