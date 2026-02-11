read_directory(struct dir_struct *dir, const char *path, const char *base, int baselen, const char **pathspec)
{
	struct path_simplify *simplify;

	if (has_symlink_leading_path(strlen(path), path))
		return dir->nr;

	simplify = create_simplify(pathspec);
	read_directory_recursive(dir, path, base, baselen, 0, simplify);
	free_simplify(simplify);
	qsort(dir->entries, dir->nr, sizeof(struct dir_entry *), cmp_name);
	qsort(dir->ignored, dir->ignored_nr, sizeof(struct dir_entry *), cmp_name);
	return dir->nr;
}
