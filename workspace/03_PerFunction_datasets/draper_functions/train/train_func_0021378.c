binary_tree_insert(struct binary_tree_descriptor *desc, void *data)
{
	int (*compare)(const void *, const void *);
	struct binary_tree_node **pp, *p;

	compare = desc->compare;
	if (compare == NULL)
	{
		error_msg("compare function is NULL");
		return -ENODATA;
	}

	pp = &desc->root;

	while ((p = *pp))
	{
		if (compare(data, p->data) < 0)
		{
			pp = &p->left;
		}
		else
		{
			pp = &p->right;
		}
	}

	p = binary_tree_malloc_node(desc, data, NULL, NULL);
	if (p == NULL)
	{
		error_msg("binary_tree_malloc_node");
		return -ENOMEM;
	}

	*pp = p;

	return 0;
}
