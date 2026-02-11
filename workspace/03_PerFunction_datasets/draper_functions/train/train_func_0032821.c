clone_mi_tree(struct mi_root *org, int shm)
{
	struct mi_root *root;

	use_shm = shm?1:0;

	root = init_mi_tree( org->code, org->reason.s, org->reason.len);
	if (root==NULL)
		goto done;

	if (clone_mi_node( &(org->node), &(root->node) )!=0 ) {
		free_mi_tree(root);
		root = NULL;
		goto done;
	}

done:
	use_shm=0;
	return root;
}
