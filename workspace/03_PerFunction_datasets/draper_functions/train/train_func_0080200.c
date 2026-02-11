get_dns_system_by_id(DYNDNS_SYSTEM_ID id)
{
	DYNDNS_SYSTEM_INFO *it;

	for (it = dns_system_table; it->id != LAST_DNS_SYSTEM; ++it)
	{
		if (it->id == id)
		{
			return &it->system;
		}
	}

	return NULL;
}
