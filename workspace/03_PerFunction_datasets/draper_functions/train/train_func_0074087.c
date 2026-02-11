update_info_refs(int force)
{
	char *path0 = xstrdup(git_path("info/refs"));
	int len = strlen(path0);
	char *path1 = xmalloc(len + 2);

	strcpy(path1, path0);
	strcpy(path1 + len, "+");

	safe_create_leading_directories(path0);
	info_ref_fp = fopen(path1, "w");
	if (!info_ref_fp)
		return error("unable to update %s", path0);
	for_each_ref(add_info_ref, NULL);
	fclose(info_ref_fp);
	rename(path1, path0);
	free(path0);
	free(path1);
	return 0;
}
