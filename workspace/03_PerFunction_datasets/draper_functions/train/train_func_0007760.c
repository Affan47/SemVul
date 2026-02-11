splitting_at_eof(struct ext2_extent_handle *handle,
			    struct extent_path *path)
{
	struct extent_path *ppp = path;
	dump_path(__func__, handle, path);

	if (handle->level == 0)
		return 0;

	do {
		if (ppp->left)
			return 0;
		ppp--;
	} while (ppp >= handle->path);

	return 1;
}
