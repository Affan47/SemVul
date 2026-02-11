cma_save_ip6_info(struct sockaddr *src_addr,
			      struct sockaddr *dst_addr,
			      struct cma_hdr *hdr,
			      __be16 local_port)
{
	struct sockaddr_in6 *ip6;

	if (src_addr) {
		ip6 = (struct sockaddr_in6 *)src_addr;
		ip6->sin6_family = AF_INET6;
		ip6->sin6_addr = hdr->dst_addr.ip6;
		ip6->sin6_port = local_port;
	}

	if (dst_addr) {
		ip6 = (struct sockaddr_in6 *)dst_addr;
		ip6->sin6_family = AF_INET6;
		ip6->sin6_addr = hdr->src_addr.ip6;
		ip6->sin6_port = hdr->port;
	}
}
