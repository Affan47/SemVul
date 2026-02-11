find_best_siblings_helper(Node *n, Node *new_leaf, Node *super_tree,
		vector<Node *> &gene_trees, int &min_distance, int &num_ties,
		multimap<int, Node*> *best_siblings, int num_siblings) {


	if (n->lchild() != NULL) {
		find_best_siblings_helper(n->lchild(), new_leaf, super_tree,
				gene_trees, min_distance, num_ties, best_siblings, num_siblings);
	}
	if (n->rchild() != NULL) {
		find_best_siblings_helper(n->rchild(), new_leaf, super_tree,
				gene_trees, min_distance, num_ties, best_siblings, num_siblings);
	}


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
	distance = rSPR_total_approx_distance(super_tree, gene_trees,
			min_distance);
{
	if (distance < min_distance) {
		best_siblings->insert(make_pair(distance, n));
		if (best_siblings->size() > num_siblings) {
			best_siblings->erase(--(best_siblings->end()));
			min_distance = (--(best_siblings->end()))->first;
		}
		num_ties = 2;
	}
	else if (distance == min_distance) {
		int r = rand();
		if (r < RAND_MAX/num_ties) {
			if (best_siblings->size() > num_siblings) {
				best_siblings->erase(--(best_siblings->end()));
				best_siblings->insert(make_pair(distance, n));
			}
		}
		num_ties++;
	}
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
