orphaned_commit_warning(struct commit *commit)
{
	struct rev_list_args args = { 0, 0, NULL };
	struct rev_info revs;

	add_one_rev_list_arg(&args, "(internal)");
	add_one_rev_list_arg(&args, sha1_to_hex(commit->object.sha1));
	add_one_rev_list_arg(&args, "--not");
	for_each_ref(add_one_ref_to_rev_list_arg, &args);
	add_one_rev_list_arg(&args, "--");
	add_one_rev_list_arg(&args, NULL);

	init_revisions(&revs, NULL);
	if (setup_revisions(args.argc - 1, args.argv, &revs, NULL) != 1)
		die(_("internal error: only -- alone should have been left"));
	if (prepare_revision_walk(&revs))
		die(_("internal error in revision walk"));
	if (!(commit->object.flags & UNINTERESTING))
		suggest_reattach(commit, &revs);
	else
		describe_detached_head(_("Previous HEAD position was"), commit);

	clear_commit_marks(commit, -1);
	for_each_ref(clear_commit_marks_from_one_ref, NULL);
}
