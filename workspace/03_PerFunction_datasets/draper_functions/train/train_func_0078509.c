rebase_alloc(const git_rebase_options *rebase_opts)
{
	git_rebase *rebase = git__calloc(1, sizeof(git_rebase));

	if (!rebase)
		return NULL;

	if (rebase_opts)
		memcpy(&rebase->options, rebase_opts, sizeof(git_rebase_options));
	else
		git_rebase_init_options(&rebase->options, GIT_REBASE_OPTIONS_VERSION);

	if (rebase_opts && rebase_opts->rewrite_notes_ref) {
		if ((rebase->options.rewrite_notes_ref = git__strdup(rebase_opts->rewrite_notes_ref)) == NULL)
			return NULL;
	}

	if ((rebase->options.checkout_options.checkout_strategy & (GIT_CHECKOUT_SAFE | GIT_CHECKOUT_FORCE)) == 0)
		rebase->options.checkout_options.checkout_strategy = GIT_CHECKOUT_SAFE;

	return rebase;
}
