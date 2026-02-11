diff_tree_combined_merge(const unsigned char *sha1,
			     int dense, struct rev_info *rev)
{
	int num_parent;
	const unsigned char (*parent)[20];
	struct commit *commit = lookup_commit(sha1);
	struct commit_list *parents;


	for (parents = commit->parents, num_parent = 0;
	     parents;
	     parents = parents->next, num_parent++)
		;

	parent = xmalloc(num_parent * sizeof(*parent));
	for (parents = commit->parents, num_parent = 0;
	     parents;
	     parents = parents->next, num_parent++)
		hashcpy((unsigned char *)(parent + num_parent),
			parents->item->object.sha1);
	diff_tree_combined(sha1, parent, num_parent, dense, rev);
}
