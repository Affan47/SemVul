mnt_get_uid(const char *username, uid_t *uid)
{
	int rc = -1;
        struct passwd pwd;
	struct passwd *pw;
	size_t sz = sysconf(_SC_GETPW_R_SIZE_MAX);
	char *buf;

	if (!username || !uid)
		return -EINVAL;
	if (sz <= 0)
		sz = 16384;

	buf = malloc(sz);
	if (!buf)
		return -ENOMEM;

	if (!getpwnam_r(username, &pwd, buf, sz, &pw) && pw) {
		*uid= pw->pw_uid;
		rc = 0;
	} else {
		DBG(UTILS, mnt_debug(
			"cannot convert '%s' username to UID", username));
	}

	free(buf);
	return rc;
}
