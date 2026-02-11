rehash_dns_vhost(void)
{
	const char *v6 = "0";
	const char *v4 = "0";
#ifdef RB_IPV6
	if(!EmptyString(ServerInfo.vhost6_dns))
		v6 = ServerInfo.vhost6_dns;
#endif
	if(!EmptyString(ServerInfo.vhost_dns))
		v4 = ServerInfo.vhost_dns;
	rb_helper_write(dns_helper, "B 0 %s %s", v4, v6);
}
