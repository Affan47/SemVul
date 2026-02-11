create_group(int op, char *groupname, int nusers, char **users)
{
	struct gfarm_group_info group;
	gfarm_error_t e;

	group.groupname = groupname;
	group.nusers = nusers;
	group.usernames = users;

	switch (op) {
	case OP_CREATE_GROUP:
		e = gfm_client_group_info_set(gfm_server, &group);
		break;
	case OP_MODIFY_GROUP:
		e = gfm_client_group_info_modify(gfm_server, &group);
		break;
	default:
		e = GFARM_ERR_INVALID_ARGUMENT;
	}
	return (e);
}
