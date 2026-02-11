rebase_normalize_opts(
	git_repository *repo,
	git_rebase_options *opts,
	const git_rebase_options *given_opts)
{
	git_rebase_options default_opts = GIT_REBASE_OPTIONS_INIT;
	git_config *config;

	if (given_opts)
		memcpy(opts, given_opts, sizeof(git_rebase_options));
	else
		memcpy(opts, &default_opts, sizeof(git_rebase_options));

	if (git_repository_config(&config, repo) < 0)
		return -1;

	if (given_opts && given_opts->rewrite_notes_ref) {
		opts->rewrite_notes_ref = git__strdup(given_opts->rewrite_notes_ref);
		GITERR_CHECK_ALLOC(opts->rewrite_notes_ref);
	} else if (git_config__get_bool_force(config, "notes.rewrite.rebase", 1)) {
		const char *rewrite_ref = git_config__get_string_force(
			config, "notes.rewriteref", NOTES_DEFAULT_REF);

		if (rewrite_ref) {
			opts->rewrite_notes_ref = git__strdup(rewrite_ref);
			GITERR_CHECK_ALLOC(opts->rewrite_notes_ref);
		}
	}

	git_config_free(config);

	return 0;
}
