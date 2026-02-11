get_gid(const char *token, gid_t *gid_p)
{
	struct group *group;

	if (get_id(token, (uid_t *)gid_p) == 0)
		return 0;
	group = getgrnam(token);
	if (group) {
		*gid_p = group->gr_gid;
		return 0;
	}
	return -1;
}
