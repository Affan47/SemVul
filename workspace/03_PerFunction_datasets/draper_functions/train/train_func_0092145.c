cmd_log_walk(struct rev_info *rev)
{
	struct commit *commit;

	if (rev->early_output)
		setup_early_output(rev);

	if (prepare_revision_walk(rev))
		die("revision walk setup failed");

	if (rev->early_output)
		finish_early_output(rev);

	while ((commit = get_revision(rev)) != NULL) {
		log_tree_commit(rev, commit);
		if (!rev->reflog_info) {

			free(commit->buffer);
			commit->buffer = NULL;
		}
		free_commit_list(commit->parents);
		commit->parents = NULL;
	}
	return 0;
}
