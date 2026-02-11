cfq_group_service_tree_del(struct cfq_rb_root *st, struct cfq_group *cfqg)
{
	struct cfq_group *pos = cfqg;
	bool propagate;


	propagate = !--pos->nr_active;
	pos->children_weight -= pos->leaf_weight;

	while (propagate) {
		struct cfq_group *parent = cfqg_parent(pos);


		WARN_ON_ONCE(pos->children_weight);
		pos->vfraction = 0;

		if (!parent)
			break;

		propagate = !--parent->nr_active;
		parent->children_weight -= pos->weight;
		pos = parent;
	}


	if (!RB_EMPTY_NODE(&cfqg->rb_node))
		cfq_rb_erase(&cfqg->rb_node, st);
}
