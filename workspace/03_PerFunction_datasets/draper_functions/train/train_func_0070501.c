unpack(const string &data, const sockaddr *saddr)
{
	string s = "";

	switch (how) {
	case WRAP_ICMP_REQUEST:
	case WRAP_ICMP_REPLY:
		s = de_icmp(data, reinterpret_cast<const sockaddr_in *>(saddr));
		break;
	case WRAP_ICMP6_REQUEST:
	case WRAP_ICMP6_REPLY:
		s = de_icmp6(data, reinterpret_cast<const sockaddr_in6 *>(saddr));
		break;
	case WRAP_DNS_REQUEST:
		s = de_dns_reply(data);
		break;
	case WRAP_DNS_REPLY:
		s = de_dns_request(data, saddr);
		break;
	default:
		;
	}
	return s;
}
