extract_ip_field(u_int32_t ip, unsigned long depth)
{
	u_int8_t ip_node[4];

	memcpy(ip_node, &ip, sizeof(ip));

	if (depth > 3)
		return 0;

	return ip_node[depth];
}
