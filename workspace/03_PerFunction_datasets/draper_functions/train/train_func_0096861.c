build_workdir_tree(const char *root, int dirs, int subs)
{
	int i, j;
	char buf[64], sub[64];

	for (i = 0; i < dirs; ++i) {
		if (i % 2 == 0) {
			p_snprintf(buf, sizeof(buf), "%s/dir%02d", root, i);
			cl_git_pass(git_futils_mkdir(buf, NULL, 0775, GIT_MKDIR_PATH));

			p_snprintf(buf, sizeof(buf), "%s/dir%02d/file", root, i);
			cl_git_mkfile(buf, buf);
			buf[strlen(buf) - 5] = '\0';
		} else {
			p_snprintf(buf, sizeof(buf), "%s/DIR%02d", root, i);
			cl_git_pass(git_futils_mkdir(buf, NULL, 0775, GIT_MKDIR_PATH));
		}

		for (j = 0; j < subs; ++j) {
			switch (j % 4) {
			case 0: p_snprintf(sub, sizeof(sub), "%s/sub%02d", buf, j); break;
			case 1: p_snprintf(sub, sizeof(sub), "%s/sUB%02d", buf, j); break;
			case 2: p_snprintf(sub, sizeof(sub), "%s/Sub%02d", buf, j); break;
			case 3: p_snprintf(sub, sizeof(sub), "%s/SUB%02d", buf, j); break;
			}
			cl_git_pass(git_futils_mkdir(sub, NULL, 0775, GIT_MKDIR_PATH));

			if (j % 2 == 0) {
				size_t sublen = strlen(sub);
				memcpy(&sub[sublen], "/file", sizeof("/file"));
				cl_git_mkfile(sub, sub);
				sub[sublen] = '\0';
			}
		}
	}
}
