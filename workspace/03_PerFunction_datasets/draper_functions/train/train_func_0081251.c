test_sibling_helper(Node *n, Node *new_leaf, Node *super_tree,
		vector<Node *> &gene_trees, int &min_distance, int &num_ties,
		Node **best_sibling) {


	int status = -1;
	if (n->parent() != NULL)
		if (n->parent()->lchild() == n)
			status = 1;
		else
			status = 2;
	Node *new_node = n->expand_parent_edge(n);
	new_node->add_child(new_leaf);


	super_tree->set_depth(0);
	super_tree->fix_depths();
	int distance;
	if (RANDOM_TREE)
		distance = 0;
	else {
		if (APPROX) {
			if (UNROOTED)
				distance = rSPR_total_approx_distance_unrooted(super_tree, gene_trees);
			else
				distance = rSPR_total_approx_distance(super_tree, gene_trees);
		}
		else {
			if (UNROOTED)
				distance = rSPR_total_distance_unrooted(super_tree, gene_trees,
						min_distance);
			else
				distance = rSPR_total_distance(super_tree, gene_trees, min_distance);
		}
	}
	if (distance < min_distance) {
		min_distance = distance;
		*best_sibling = n;
		num_ties = 2;
	}
	else if (distance == min_distance) {
		int r = rand();
		if (r < RAND_MAX/num_ties) {
			min_distance = distance;
			*best_sibling = n;
		}
		num_ties++;
	}


	new_leaf->cut_parent();

	new_node = new_node->undo_expand_parent_edge();
	delete new_node;

	if (n->parent() != NULL)
		if ((status == 1 && n->parent()->lchild() != n)
				|| (status == 2 && n->parent()->rchild() != n)) {
			Node *rc = n->parent()->lchild();
			rc->cut_parent();
			n->parent()->add_child(rc);
		}
	super_tree->set_depth(0);
	super_tree->fix_depths();


}
