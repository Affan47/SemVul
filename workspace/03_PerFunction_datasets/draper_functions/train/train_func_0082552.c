get_group_id_from_group_name (const char *group_name, uid_t *gid)
{
	struct group *group;

	g_assert (gid != NULL);

	group = getgrnam (group_name);

	if (group == NULL) {
		return FALSE;
	}

	*gid = group->gr_gid;

	return TRUE;
}
