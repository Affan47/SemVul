isc_sockaddr_any(isc_sockaddr_t *sockaddr)
{
	memset(sockaddr, 0, sizeof(*sockaddr));
	sockaddr->type.sin.sin_family = AF_INET;
#ifdef ISC_PLATFORM_HAVESALEN
	sockaddr->type.sin.sin_len = sizeof(sockaddr->type.sin);
#endif
	sockaddr->type.sin.sin_addr.s_addr = INADDR_ANY;
	sockaddr->type.sin.sin_port = 0;
	sockaddr->length = sizeof(sockaddr->type.sin);
	ISC_LINK_INIT(sockaddr, link);
}
