git_attr_path__init(
	git_attr_path *info, const char *path, const char *base)
{

	git_buf_init(&info->full, 0);

	if (base != NULL && git_path_root(path) < 0) {
		if (git_buf_joinpath(&info->full, base, path) < 0)
			return -1;
		info->path = info->full.ptr + strlen(base);
	} else {
		if (git_buf_sets(&info->full, path) < 0)
			return -1;
		info->path = info->full.ptr;
	}


	while (info->full.size > 0) {
		if (info->full.ptr[info->full.size - 1] != '/')
			break;
		info->full.size--;
	}
	info->full.ptr[info->full.size] = '\0';


	while (*info->path == '/')
		info->path++;


	info->basename = strrchr(info->path, '/');
	if (info->basename)
		info->basename++;
	if (!info->basename || !*info->basename)
		info->basename = info->path;

	info->is_dir = (int)git_path_isdir(info->full.ptr);

	return 0;
}
