read_directory(struct dir_struct *dir, const char *path, int len, const char **pathspec)
{
	struct path_simplify *simplify;

	if (has_symlink_leading_path(path, len))
		return dir->nr;

	simplify = create_simplify(pathspec);
	if (!len || treat_leading_path(dir, path, len, simplify))
		read_directory_recursive(dir, path, len, 0, simplify);
	free_simplify(simplify);
	qsort(dir->entries, dir->nr, sizeof(struct dir_entry *), cmp_name);
	qsort(dir->ignored, dir->ignored_nr, sizeof(struct dir_entry *), cmp_name);
	return dir->nr;
}
