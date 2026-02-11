user_statfs(const char __user *pathname, struct kstatfs *st)
{
	struct path path;
	int error;
	unsigned int lookup_flags = LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT;
retry:
	error = user_path_at(AT_FDCWD, pathname, lookup_flags, &path);
	if (!error) {
		error = vfs_statfs(&path, st);
		path_put(&path);
		if (retry_estale(error, lookup_flags)) {
			lookup_flags |= LOOKUP_REVAL;
			goto retry;
		}
	}
	return error;
}
