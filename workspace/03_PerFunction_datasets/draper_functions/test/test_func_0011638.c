dir_add_name(struct dir_struct *dir, const char *pathname, int len)
{
	if (cache_name_pos(pathname, len) >= 0)
		return NULL;

	ALLOC_GROW(dir->entries, dir->nr, dir->alloc);
	return dir->entries[dir->nr++] = dir_entry_new(pathname, len);
}
