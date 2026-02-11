check_tracking_name(const char *refname, const unsigned char *sha1,
			       int flags, void *cb_data)
{
	struct tracking_name_data *cb = cb_data;
	const char *slash;

	if (prefixcmp(refname, "refs/remotes/"))
		return 0;
	slash = strchr(refname + 13, '/');
	if (!slash || strcmp(slash + 1, cb->name))
		return 0;
	if (cb->remote) {
		cb->unique = 0;
		return 0;
	}
	cb->remote = xstrdup(refname);
	return 0;
}
