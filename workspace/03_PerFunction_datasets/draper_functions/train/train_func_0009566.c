cavan_data_pool_alloc(struct cavan_data_pool *pool)
{
	void *data;
	struct double_link_node *node;
	struct cavan_data_pool_node *pool_node;

	node = double_link_pop(&pool->link);
	if (node)
	{
		return double_link_get_container(&pool->link, node);
	}

	data = malloc(pool->node_size);
	if (data == NULL)
	{
		pr_error_info("malloc");
		return NULL;
	}

	pool_node = cavan_data_pool_to_node(pool, data);
	pool_node->destroy = cavan_data_pool_node_destroy2;
	double_link_node_init(&pool_node->node);

	return data;
}
