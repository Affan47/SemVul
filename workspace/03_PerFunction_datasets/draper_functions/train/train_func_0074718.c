jdns_list_remove(jdns_list_t *a, void *item)
{
	int n;
	int pos = -1;
	for(n = 0; n < a->count; ++n)
	{
		if(a->item[n] == item)
		{
			pos = n;
			break;
		}
	}
	if(pos == -1)
		return;

	jdns_list_remove_at(a, pos);
}
