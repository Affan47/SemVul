get_ref_dir(const char *submodule, const char *base,
				    struct ref_list *list)
{
	DIR *dir;
	const char *path;

	if (submodule)
		path = git_path_submodule(submodule, "%s", base);
	else
		path = git_path("%s", base);


	dir = opendir(path);

	if (dir) {
		struct dirent *de;
		int baselen = strlen(base);
		char *ref = xmalloc(baselen + 257);

		memcpy(ref, base, baselen);
		if (baselen && base[baselen-1] != '/')
			ref[baselen++] = '/';

		while ((de = readdir(dir)) != NULL) {
			unsigned char sha1[20];
			struct stat st;
			int flag;
			int namelen;
			const char *refdir;

			if (de->d_name[0] == '.')
				continue;
			namelen = strlen(de->d_name);
			if (namelen > 255)
				continue;
			if (has_extension(de->d_name, ".lock"))
				continue;
			memcpy(ref + baselen, de->d_name, namelen+1);
			refdir = submodule
				? git_path_submodule(submodule, "%s", ref)
				: git_path("%s", ref);
			if (stat(refdir, &st) < 0)
				continue;
			if (S_ISDIR(st.st_mode)) {
				list = get_ref_dir(submodule, ref, list);
				continue;
			}
			if (submodule) {
				hashclr(sha1);
				flag = 0;
				if (resolve_gitlink_ref(submodule, ref, sha1) < 0) {
					hashclr(sha1);
					flag |= REF_BROKEN;
				}
			} else
				if (!resolve_ref(ref, sha1, 1, &flag)) {
					hashclr(sha1);
					flag |= REF_BROKEN;
				}
			list = add_ref(ref, sha1, flag, list, NULL);
		}
		free(ref);
		closedir(dir);
	}
	return sort_ref_list(list);
}
