tree_free(struct tree *t)
{
	int i;

	if (t == NULL)
		return;
	archive_string_free(&t->path);
#if defined(HAVE_READDIR_R)
	free(t->dirent);
#endif
	free(t->sparse_list);
	for (i = 0; i < t->max_filesystem_id; i++)
		free(t->filesystem_table[i].allocation_ptr);
	free(t->filesystem_table);
	free(t);
}
