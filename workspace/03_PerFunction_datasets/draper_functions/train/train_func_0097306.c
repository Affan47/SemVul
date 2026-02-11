get_next_req_id(jdns_session_t *s)
{
	int n, k, id;
	id = -1;
	while(id == -1)
	{
		id = _int_wrap(&s->next_req_id, 1);


		for(n = 0; n < s->queries->count; ++n)
		{
			query_t *q = (query_t *)s->queries->item[n];
			for(k = 0; k < q->req_ids_count; ++k)
			{
				if(q->req_ids[k] == id)
				{
					id = -1;
					break;
				}
			}
			if(id == -1)
				break;
		}


		for(n = 0; n < s->published->count; ++n)
		{
			if(((published_item_t *)s->published->item[n])->id == id)
			{
				id = -1;
				break;
			}
		}


		for(n = 0; n < s->held_req_ids_count; ++n)
		{
			if(s->held_req_ids[n] == id)
			{
				id = -1;
				break;
			}
		}
	}
	return id;
}
