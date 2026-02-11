merge_recursive(struct merge_options *o,
		    struct commit *h1,
		    struct commit *h2,
		    struct commit_list *ca,
		    struct commit **result)
{
	struct commit_list *iter;
	struct commit *merged_common_ancestors;
	struct tree *mrtree = mrtree;
	int clean;

	if (show(o, 4)) {
		output(o, 4, "Merging:");
		output_commit_title(o, h1);
		output_commit_title(o, h2);
	}

	if (!ca) {
		ca = get_merge_bases(h1, h2, 1);
		ca = reverse_commit_list(ca);
	}

	if (show(o, 5)) {
		output(o, 5, "found %u common ancestor(s):", commit_list_count(ca));
		for (iter = ca; iter; iter = iter->next)
			output_commit_title(o, iter->item);
	}

	merged_common_ancestors = pop_commit(&ca);
	if (merged_common_ancestors == NULL) {

		struct tree *tree = xcalloc(1, sizeof(struct tree));

		tree->object.parsed = 1;
		tree->object.type = OBJ_TREE;
		pretend_sha1_file(NULL, 0, OBJ_TREE, tree->object.sha1);
		merged_common_ancestors = make_virtual_commit(tree, "ancestor");
	}

	for (iter = ca; iter; iter = iter->next) {
		const char *saved_b1, *saved_b2;
		o->call_depth++;


		discard_cache();
		saved_b1 = o->branch1;
		saved_b2 = o->branch2;
		o->branch1 = "Temporary merge branch 1";
		o->branch2 = "Temporary merge branch 2";
		merge_recursive(o, merged_common_ancestors, iter->item,
				NULL, &merged_common_ancestors);
		o->branch1 = saved_b1;
		o->branch2 = saved_b2;
		o->call_depth--;

		if (!merged_common_ancestors)
			die("merge returned no commit");
	}

	discard_cache();
	if (!o->call_depth)
		read_cache();

	o->ancestor = "merged common ancestors";
	clean = merge_trees(o, h1->tree, h2->tree, merged_common_ancestors->tree,
			    &mrtree);

	if (o->call_depth) {
		*result = make_virtual_commit(mrtree, "merged tree");
		commit_list_insert(h1, &(*result)->parents);
		commit_list_insert(h2, &(*result)->parents->next);
	}
	flush_output(o);
	return clean;
}
