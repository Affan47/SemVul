create_default_files(const char *git_dir, const char *template_path)
{
	unsigned len = strlen(git_dir);
	static char path[PATH_MAX];
	unsigned char sha1[20];
	struct stat st1;
	char repo_version_string[10];
	int reinit;
	int filemode;

	if (len > sizeof(path)-50)
		die("insane git directory %s", git_dir);
	memcpy(path, git_dir, len);

	if (len && path[len-1] != '/')
		path[len++] = '/';


	strcpy(path + len, "refs");
	safe_create_dir(path, 1);
	strcpy(path + len, "refs/heads");
	safe_create_dir(path, 1);
	strcpy(path + len, "refs/tags");
	safe_create_dir(path, 1);


	path[len] = 0;
	copy_templates(path, len, template_path);

	git_config(git_default_config);


	if (shared_repository) {
		path[len] = 0;
		adjust_shared_perm(path);
		strcpy(path + len, "refs");
		adjust_shared_perm(path);
		strcpy(path + len, "refs/heads");
		adjust_shared_perm(path);
		strcpy(path + len, "refs/tags");
		adjust_shared_perm(path);
	}


	strcpy(path + len, "HEAD");
	reinit = !read_ref("HEAD", sha1);
	if (!reinit) {
		if (create_symref("HEAD", "refs/heads/master", NULL) < 0)
			exit(1);
	}


	sprintf(repo_version_string, "%d", GIT_REPO_VERSION);
	git_config_set("core.repositoryformatversion", repo_version_string);

	path[len] = 0;
	strcpy(path + len, "config");


	filemode = TEST_FILEMODE;
	if (TEST_FILEMODE && !lstat(path, &st1)) {
		struct stat st2;
		filemode = (!chmod(path, st1.st_mode ^ S_IXUSR) &&
				!lstat(path, &st2) &&
				st1.st_mode != st2.st_mode);
	}
	git_config_set("core.filemode", filemode ? "true" : "false");

	if (is_bare_repository()) {
		git_config_set("core.bare", "true");
	}
	else {
		git_config_set("core.bare", "false");

		if (log_all_ref_updates == -1)
		    git_config_set("core.logallrefupdates", "true");
	}
	return reinit;
}
