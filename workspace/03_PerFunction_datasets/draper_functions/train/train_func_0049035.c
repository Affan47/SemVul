group_mgmt_check_moved(const char *groupname)
{
	FILE *queue;
	char buff[NAME_MAX], queue_name[NAME_MAX];
	snprintf(queue_name, NAME_MAX, "%s%cgroup_actions_queue",
		config_dir, G_DIR_SEPARATOR);

	queue = fopen(queue_name, "r");
	if (!queue)
		return 0;

	while (fgets(buff, sizeof(buff), queue) != NULL) {
		char **tokens = ay_strsplit(buff, "\t", -1);

		char *oldgroup = tokens[2];


		if (oldgroup && !strcmp(oldgroup, groupname)) {
			fclose(queue);
			return 1;
		}
		ay_strfreev(tokens);
	}

	fclose(queue);
	return 0;
}
