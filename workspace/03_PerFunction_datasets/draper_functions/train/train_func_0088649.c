rb_tree_insert_r(struct rb_tree* tree, struct rb_node* node, const void* key, const void* value)
{
	int res;
	if (!node)
		return create_node(tree, key, value);

	res = tree->compare(node->key, key);
	if (!res)
	{
		puts("Node already exists!");
		return NULL;
	}
	else
	{
		int dir = res < 0;
		node->link[dir] = rb_tree_insert_r(tree, node->link[dir], key, value);

		if (is_red(node->link[dir]))
		{
			if (is_red(node->link[!dir]))
			{

				node->red = 1;
				node->link[0]->red = 0;
				node->link[1]->red = 0;
			}
			else
			{

				if (is_red(node->link[dir]->link[dir]))
					node = rb_tree_rotate_single(node, !dir);
				else if (is_red(node->link[dir]->link[!dir]))
					node = rb_tree_rotate_double(node, !dir);
			}
		}
	}
	return node;
}
