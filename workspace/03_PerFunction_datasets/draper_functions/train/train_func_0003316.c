get_marker_label(struct node *tree, const char *label,
				struct node **node, struct property **prop)
{
	struct marker *m;
	struct property *p;
	struct node *c;

	*node = tree;

	for_each_property(tree, p) {
		*prop = p;
		m = p->val.markers;
		for_each_marker_of_type(m, LABEL)
			if (streq(m->ref, label))
				return m;
	}

	for_each_child(tree, c) {
		m = get_marker_label(c, label, node, prop);
		if (m)
			return m;
	}

	*prop = NULL;
	*node = NULL;
	return NULL;
}
