network_service_open(struct network_service *service, const struct network_url *url, int flags)
{
	int ret;
	const struct network_protocol_desc *desc;

	pd_bold_info("URL = %s", network_url_tostring(url, NULL, 0, NULL));

	if (service->type == NETWORK_PROTOCOL_UNIX_TCP || service->type == NETWORK_PROTOCOL_UNIX_UDP)
	{
		ret = mkdir_hierarchy(CAVAN_NETWORK_TEMP_PATH, 0777);
		if (ret < 0)
		{
			pr_red_info("mkdir_hierarchy %s", CAVAN_NETWORK_TEMP_PATH);
			return ret;
		}
	}

	desc = network_get_protocol_by_name(url->protocol);
	if (desc == NULL)
	{
		pr_red_info("network_get_protocol_by_name");
		return -EINVAL;
	}

	return network_protocol_open_service(desc, service, url, flags);
}
