print_ref_list(int kinds, int detached, int verbose, int abbrev)
{
	int i;
	struct ref_list ref_list;

	memset(&ref_list, 0, sizeof(ref_list));
	ref_list.kinds = kinds;
	for_each_ref(append_ref, &ref_list);

	qsort(ref_list.list, ref_list.index, sizeof(struct ref_item), ref_cmp);

	detached = (detached && (kinds & REF_LOCAL_BRANCH));
	if (detached) {
		struct ref_item item;
		item.name = xstrdup("(no branch)");
		item.kind = REF_LOCAL_BRANCH;
		hashcpy(item.sha1, head_sha1);
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
