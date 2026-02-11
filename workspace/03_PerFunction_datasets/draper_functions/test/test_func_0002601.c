dir_free(Dir dir)
{
	DirEntry entry;

	while ((entry = RB_MIN(rbdir, dir)) != NULL)
		rbdir_entry_delete(dir, entry);
	free(dir);
}
