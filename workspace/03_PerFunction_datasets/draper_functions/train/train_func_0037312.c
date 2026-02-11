graph_has_tooltips(struct graph *g)
{
	struct flist_head *entry;
	struct graph_label *i;

	flist_for_each(entry, &g->label_list) {
		i = flist_entry(entry, struct graph_label, list);

		if (!prio_tree_empty(&i->prio_tree))
			return 1;
	}

	return 0;
}
