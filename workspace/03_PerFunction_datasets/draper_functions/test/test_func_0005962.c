client_delete(RADCLIENT_LIST *clients, RADCLIENT *client)
{
	if (!client) return;

	if (!clients) clients = root_clients;

	if (!client->dynamic) return;

	rad_assert((client->prefix >= 0) && (client->prefix <= 128));

	client->dynamic = 2;

#ifdef WITH_STATS
	rbtree_deletebydata(tree_num, client);
#endif
	rbtree_deletebydata(clients->trees[client->prefix], client);
}
