browse_host_dl_search_closed(struct browse_ctx *bc, gnet_search_t sh)
{
	g_assert(bc != NULL);
	g_assert(bc->sh == sh);

	bc->closed = TRUE;
}
