fr_packet_list_yank(fr_packet_list_t *pl, RADIUS_PACKET *request)
{
	rbnode_t *node;

	if (!pl || !request) return;

	node = rbtree_find(pl->tree, &request);
	if (!node) return;

	rbtree_delete(pl->tree, node);
}
