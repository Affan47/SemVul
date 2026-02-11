check_blocklist(struct blocklist_s *p, const RFC1035_ADDR *ia)
{
	if (IN6_IS_ADDR_V4MAPPED(ia))
	{
	struct in_addr ia4;

		memcpy(&ia4, (const char *)ia + 12, 4);
		check_blocklist_ipv4(p, &ia4);
	}
}
