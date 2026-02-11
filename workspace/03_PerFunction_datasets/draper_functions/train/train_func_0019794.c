_cache_remove_all_of_record(jdns_session_t *s, const jdns_rr_t *record)
{
	int n;
	for(n = 0; n < s->cache->count; ++n)
	{
		cache_item_t *i = (cache_item_t *)s->cache->item[n];
		if(i->record && _cmp_rr(i->record, record))
		{
			jdns_string_t *str = _make_printable_cstr((const char *)i->qname);
			_debug_line(s, "cache del [%s]", str->data);
			jdns_string_delete(str);
			list_remove(s->cache, i);
			--n;
		}
	}
}
