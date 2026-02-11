jdns_string_set(jdns_string_t *s, const unsigned char *str, int str_len)
{
	if(s->data)
		jdns_free(s->data);
	s->data = (unsigned char *)jdns_alloc(str_len + 1);
	memcpy(s->data, str, str_len);
	s->data[str_len] = 0;
	s->size = str_len;
}
