SPF_request_set_ipv4_str(SPF_request_t *sr, const char *astr)
{
	struct in_addr	addr;
	if (astr == NULL)
		astr = "0.0.0.0";
	if (inet_pton(AF_INET, astr, &addr) <= 0)
		return SPF_E_INVALID_IP4;
	return SPF_request_set_ipv4(sr, addr);
}
