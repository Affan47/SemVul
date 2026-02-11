parse_addresses(char *str, linked_list_t *hosts,
							linked_list_t *ranges)
{
	enumerator_t *enumerator;
	traffic_selector_t *ts;

	enumerator = enumerator_create_token(str, ",", " ");
	while (enumerator->enumerate(enumerator, &str))
	{
		ts = make_subnet(str);
		if (ts)
		{
			ranges->insert_last(ranges, ts);
			continue;
		}
		ts = make_range(str);
		if (ts)
		{
			ranges->insert_last(ranges, ts);
			continue;
		}
		hosts->insert_last(hosts, strdup(str));
	}
	enumerator->destroy(enumerator);
}
