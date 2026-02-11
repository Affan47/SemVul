push_one_attr(void *ref, git_buf *path)
{
	int error = 0, n_src, i;
	attr_walk_up_info *info = (attr_walk_up_info *)ref;
	git_attr_file_source src[2];

	n_src = git_attr_cache__decide_sources(
		info->flags, info->workdir != NULL, info->index != NULL, src);

	for (i = 0; !error && i < n_src; ++i)
		error = git_attr_cache__push_file(
			info->repo, path->ptr, GIT_ATTR_FILE, src[i],
			git_attr_file__parse_buffer, NULL, info->files);

	return error;
}
