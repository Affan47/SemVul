parse_chown_usergroup_or_die(struct bb_uidgid_t *u, char *user_group)
{
	char *group;


	group = strchr(user_group, '.');
	if (!group)
		group = strchr(user_group, ':');
	else
		*group = ':';


	if (!group) {
		u->uid = get_ug_id(user_group, xuname2uid);
	} else if (group == user_group) {
		u->gid = get_ug_id(group + 1, xgroup2gid);
	} else {
		if (!group[1])
			*group = '\0';
		xget_uidgid(u, user_group);
	}
}
