cproxy_async_http_request(struct cproxy *cp)
{
	g_assert(cp != NULL);
	g_assert(CPROXY_MAGIC == cp->magic);

	cp->udp_ev = cq_main_insert(1, cproxy_http_start, cp);
}
