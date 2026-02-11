setup_empty_tmp_dir()
{
	char path[GIT_PATH_MAX];

	if (p_mkdir(empty_tmp_dir, 0755))
		return -1;

	git_path_join(path, empty_tmp_dir, "/one");
	if (p_mkdir(path, 0755))
		return -1;

	git_path_join(path, empty_tmp_dir, "/one/two_one");
	if (p_mkdir(path, 0755))
		return -1;

	git_path_join(path, empty_tmp_dir, "/one/two_two");
	if (p_mkdir(path, 0755))
		return -1;

	git_path_join(path, empty_tmp_dir, "/one/two_two/three");
	if (p_mkdir(path, 0755))
		return -1;

	git_path_join(path, empty_tmp_dir, "/two");
	if (p_mkdir(path, 0755))
		return -1;

	return 0;
}
