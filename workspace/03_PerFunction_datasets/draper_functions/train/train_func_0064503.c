git_config_early(config_fn_t fn, void *data, const char *repo_config)
{
	int ret = 0, found = 0;
	const char *home = NULL;


	if (config_exclusive_filename)
		return git_config_from_file(fn, config_exclusive_filename, data);
	if (git_config_system() && !access(git_etc_gitconfig(), R_OK)) {
		ret += git_config_from_file(fn, git_etc_gitconfig(),
					    data);
		found += 1;
	}

	home = getenv("HOME");
	if (home) {
		char *user_config = xstrdup(mkpath("%s/.gitconfig", home));
		if (!access(user_config, R_OK)) {
			ret += git_config_from_file(fn, user_config, data);
			found += 1;
		}
		free(user_config);
	}

	if (repo_config && !access(repo_config, R_OK)) {
		ret += git_config_from_file(fn, repo_config, data);
		found += 1;
	}

	switch (git_config_from_parameters(fn, data)) {
	case -1:
		ret--;
		break;
	case 0:
		break;
	default:
		found++;
		break;
	}

	return ret == 0 ? found : ret;
}
