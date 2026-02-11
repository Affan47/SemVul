setup_standard_excludes(struct dir_struct *dir)
{
	const char *path;

	dir->exclude_per_dir = ".gitignore";
	path = git_path("info/exclude");
	if (!access(path, R_OK))
		add_excludes_from_file(dir, path);
	if (excludes_file && !access(excludes_file, R_OK))
		add_excludes_from_file(dir, excludes_file);
}
