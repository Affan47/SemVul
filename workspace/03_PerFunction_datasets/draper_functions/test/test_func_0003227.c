xmalloc_readlink_or_warn(const char *path)
{
	char *buf = xmalloc_readlink(path);
	if (!buf) {

		const char *errmsg = "not a symlink";
		int err = errno;
		if (err != EINVAL)
			errmsg = strerror(err);
		bb_error_msg("%s: cannot read link: %s", path, errmsg);
	}
	return buf;
}
