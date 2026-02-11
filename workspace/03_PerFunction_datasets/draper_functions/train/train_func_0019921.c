__uwb_addr_print(char *buf, size_t buf_size, const unsigned char *addr,
			int type)
{
	size_t result;
	if (type)
		result = scnprintf(buf, buf_size, "%pM", addr);
	else
		result = scnprintf(buf, buf_size, "%02x:%02x",
				  addr[1], addr[0]);
	return result;
}
