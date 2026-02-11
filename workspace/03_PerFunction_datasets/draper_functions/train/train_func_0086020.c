print_ip(const struct ap_session *ses, char *buf)
{
	u_inet_ntoa(ses->ipv4 ? ses->ipv4->peer_addr : 0, buf);
}
