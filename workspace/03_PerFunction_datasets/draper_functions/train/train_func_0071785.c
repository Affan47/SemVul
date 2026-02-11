iwpm_print_sockaddr(struct sockaddr_storage *sockaddr, char *msg)
{
	struct sockaddr_in6 *sockaddr_v6;
	struct sockaddr_in *sockaddr_v4;

	switch (sockaddr->ss_family) {
	case AF_INET:
		sockaddr_v4 = (struct sockaddr_in *)sockaddr;
		pr_debug("%s IPV4 %pI4: %u(0x%04X)\n",
			msg, &sockaddr_v4->sin_addr,
			ntohs(sockaddr_v4->sin_port),
			ntohs(sockaddr_v4->sin_port));
		break;
	case AF_INET6:
		sockaddr_v6 = (struct sockaddr_in6 *)sockaddr;
		pr_debug("%s IPV6 %pI6: %u(0x%04X)\n",
			msg, &sockaddr_v6->sin6_addr,
			ntohs(sockaddr_v6->sin6_port),
			ntohs(sockaddr_v6->sin6_port));
		break;
	default:
		break;
	}
}
