gf_sk_get_remote_address(GF_Socket *sock, char *buf)
{
#ifdef GPAC_HAS_IPV6
	char clienthost[NI_MAXHOST];
 	struct sockaddr_in6 * addrptr = (struct sockaddr_in6 *)(&sock->dest_addr_len);
	if (!sock || sock->socket) return GF_BAD_PARAM;
	if (getnameinfo((struct sockaddr *)addrptr, sock->dest_addr_len, clienthost, sizeof(clienthost), NULL, 0, NI_NUMERICHOST))
		return GF_IP_ADDRESS_NOT_FOUND;
	strcpy(buf, clienthost);
#else
	if (!sock || !sock->socket) return GF_BAD_PARAM;
	strcpy(buf, inet_ntoa(sock->dest_addr.sin_addr));
#endif
	return GF_OK;
}
