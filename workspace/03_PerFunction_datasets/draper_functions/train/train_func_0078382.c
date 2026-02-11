uman_init()
{
	struct hub_user_manager* users = (struct hub_user_manager*) hub_malloc_zero(sizeof(struct hub_user_manager));
	if (!users)
		return NULL;

	users->list = list_create();
	users->nickmap = rb_tree_create(uman_map_compare, NULL, NULL);
	users->cidmap = rb_tree_create(uman_map_compare, NULL, NULL);
	users->sids = sid_pool_create(net_get_max_sockets());

	return users;
}
