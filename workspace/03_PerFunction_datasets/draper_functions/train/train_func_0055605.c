repo_git_add(uint32_t depth, uint32_t *path, struct repo_dirent *dent)
{
	if (repo_dirent_is_dir(dent))
		repo_git_add_r(depth, path, repo_dir_from_dirent(dent));
	else
		fast_export_modify(depth, path,
				   dent->mode, dent->content_offset);
}
