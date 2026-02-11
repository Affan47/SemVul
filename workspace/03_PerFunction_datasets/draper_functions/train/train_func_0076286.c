add_child(struct rnode *parent, struct rnode *child)
{
	child->parent = parent;

	if (0 == parent->child_count)
		parent->first_child = child;
	else
		parent->last_child->next_sibling = child;

	parent->child_count++;
	parent->last_child = child;
}
