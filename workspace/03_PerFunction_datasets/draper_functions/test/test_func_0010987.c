create_node(int level, int key, object *obj)
{
	int i;
	node *nd = (node *)malloc(sizeof(node) + level * sizeof(node *));
	nd->obj = obj;
	nd->key = key;

	for (i = 0; i < level; i++) {
		nd->forward[i] = NULL;
	}

	return nd;
}
