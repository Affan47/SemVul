__archive_rb_tree_insert_node(struct archive_rb_tree *rbt,
    struct archive_rb_node *self)
{
	archive_rbto_compare_nodes_fn compare_nodes = rbt->rbt_ops->rbto_compare_nodes;
	struct archive_rb_node *parent, *tmp;
	unsigned int position;
	int rebalance;

	tmp = rbt->rbt_root;


	parent = (struct archive_rb_node *)(void *)&rbt->rbt_root;
	position = RB_DIR_LEFT;


	while (!RB_SENTINEL_P(tmp)) {
		const signed int diff = (*compare_nodes)(tmp, self);
		if (diff == 0) {


			return F;
		}
		parent = tmp;
		position = (diff > 0);
		tmp = parent->rb_nodes[position];
	}


	RB_SET_FATHER(self, parent);
	RB_SET_POSITION(self, position);
	if (parent == (struct archive_rb_node *)(void *)&rbt->rbt_root) {
		RB_MARK_BLACK(self);
		rebalance = F;
	} else {


		RB_MARK_RED(self);
		rebalance = RB_RED_P(parent);
	}
	self->rb_left = parent->rb_nodes[position];
	self->rb_right = parent->rb_nodes[position];
	parent->rb_nodes[position] = self;


	if (rebalance)
		__archive_rb_tree_insert_rebalance(rbt, self);

	return T;
}
