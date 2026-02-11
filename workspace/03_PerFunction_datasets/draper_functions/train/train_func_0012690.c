grpassign_set(struct gfarm_group_info *info)
{
	const char *paramValues[2];
	int i;
	gfarm_error_t e;

	if (info->usernames == NULL)
		return (GFARM_ERR_NO_ERROR);
	for (i = 0; i < info->nusers; i++) {
		paramValues[0] = info->groupname;
		paramValues[1] = info->usernames[i];
		e = gfarm_pgsql_insert_and_log(
			"INSERT INTO "
			    "GfarmGroupAssignment (groupname, username) "
			    "VALUES ($1, $2)",
			2,
			NULL,
			paramValues,
			NULL,
			NULL,
			0,
			"pgsql_grpassign_set");
		if (e != GFARM_ERR_NO_ERROR) {
			gflog_debug(GFARM_MSG_1002159,
				"gfarm_pgsql_insert_and_log() failed");
			return (e);
		}
	}
	return (GFARM_ERR_NO_ERROR);
}
