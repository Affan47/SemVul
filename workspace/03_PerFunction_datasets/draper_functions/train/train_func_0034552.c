acl_is_ip_banned(struct acl_handle* handle, const char* ip_address)
{
	struct ip_addr_encap raw;
	struct ip_range* info;

	ip_convert_to_binary(ip_address, &raw);
	LIST_FOREACH(struct ip_range*, info, handle->networks,
	{
		if (ip_in_range(&raw, info))
			return 1;
	});
	return 0;
}
