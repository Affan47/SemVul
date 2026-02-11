check_against_blacklist(struct ip_addr *ip, str *text,
			unsigned short port, unsigned short proto)
{
	unsigned int i;

	for(i = 0 ; i < used_heads ; i++)
		if( (bl_marker&(1<<i)) &&
		check_against_rule_list(ip, text, port, proto, i))
			return 1;
	return 0;
}
