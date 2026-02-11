print_ref_list(int kinds, int detached, int verbose, int abbrev, struct commit_list *with_commit)
{
	int i;
	struct ref_list ref_list;
	struct commit *head_commit = lookup_commit_reference_gently(head_sha1, 1);

	memset(&ref_list, 0, sizeof(ref_list));
	ref_list.kinds = kinds;
	ref_list.with_commit = with_commit;
	if (merge_filter != NO_FILTER)
		init_revisions(&ref_list.revs, NULL);
	for_each_ref(append_ref, &ref_list);
	if (merge_filter != NO_FILTER) {
		struct commit *filter;
		filter = lookup_commit_reference_gently(merge_filter_ref, 0);
		filter->object.flags |= UNINTERESTING;
		add_pending_object(&ref_list.revs,
				   (struct object *) filter, "");
		ref_list.revs.limited = 1;
		prepare_revision_walk(&ref_list.revs);
		if (verbose)
			ref_list.maxwidth = calc_maxwidth(&ref_list);
	}

	qsort(ref_list.list, ref_list.index, sizeof(struct ref_item), ref_cmp);

	detached = (detached && (kinds & REF_LOCAL_BRANCH));
	if (detached && head_commit && has_commit(head_commit, with_commit)) {
		struct ref_item item;
		item.name = xstrdup("(no branch)");
		item.kind = REF_LOCAL_BRANCH;
		item.commit = head_commit;
		if (strlen(item.name) > ref_list.maxwidth)
			ref_list.maxwidth = strlen(item.name);
		print_ref_item(&item, ref_list.maxwidth, verbose, abbrev, 1);
		free(item.name);
	}

	for (i = 0; i < ref_list.index; i++) {
		int current = !detached &&
			(ref_list.list[i].kind == REF_LOCAL_BRANCH) &&
			!strcmp(ref_list.list[i].name, head);
		print_ref_item(&ref_list.list[i], ref_list.maxwidth, verbose,
			       abbrev, current);
	}

	free_ref_list(&ref_list);
}
