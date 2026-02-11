git_checkout_tree(
	git_repository *repo,
	const git_object *treeish,
	const git_checkout_options *opts)
{
	int error;
	git_tree *tree = NULL;
	git_iterator *tree_i = NULL;

	if (!treeish && !repo) {
		giterr_set(GITERR_CHECKOUT,
			"Must provide either repository or tree to checkout");
		return -1;
	}
	if (treeish && repo && git_object_owner(treeish) != repo) {
		giterr_set(GITERR_CHECKOUT,
			"Object to checkout does not match repository");
		return -1;
	}

	if (!repo)
		repo = git_object_owner(treeish);

	if (treeish) {
		if (git_object_peel((git_object **)&tree, treeish, GIT_OBJ_TREE) < 0) {
			giterr_set(
				GITERR_CHECKOUT, "Provided object cannot be peeled to a tree");
			return -1;
		}
	}
	else {
		if ((error = checkout_lookup_head_tree(&tree, repo)) < 0) {
			if (error != GIT_EUNBORNBRANCH)
				giterr_set(
					GITERR_CHECKOUT,
					"HEAD could not be peeled to a tree and no treeish given");
			return error;
		}
	}

	if (!(error = git_iterator_for_tree(&tree_i, tree, 0, NULL, NULL)))
		error = git_checkout_iterator(tree_i, opts);

	git_iterator_free(tree_i);
	git_tree_free(tree);

	return error;
}
