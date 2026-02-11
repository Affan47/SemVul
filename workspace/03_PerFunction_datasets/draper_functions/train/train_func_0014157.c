iova_insert_rbtree(struct rb_root *root, struct iova *iova)
{
	struct rb_node **new = &(root->rb_node), *parent = NULL;

	while (*new) {
		struct iova *this = container_of(*new, struct iova, node);

		parent = *new;

		if (iova->pfn_lo < this->pfn_lo)
			new = &((*new)->rb_left);
		else if (iova->pfn_lo > this->pfn_lo)
			new = &((*new)->rb_right);
		else
			BUG();
	}

	rb_link_node(&iova->node, parent, new);
	rb_insert_color(&iova->node, root);
}
