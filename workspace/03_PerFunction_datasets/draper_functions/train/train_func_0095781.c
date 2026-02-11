cg_rd_ctrl_file(const char *subsys, const char *cgroup,
					const char *file, char **value)
{
	char path[FILENAME_MAX];
	FILE *ctrl_file = NULL;
	int ret;

	if (!cg_build_path_locked(cgroup, path, subsys))
		return ECGFAIL;

	strncat(path, file, sizeof(path) - strlen(path));
	ctrl_file = fopen(path, "re");
	if (!ctrl_file)
		return ECGROUPVALUENOTEXIST;

	*value = calloc(CG_VALUE_MAX, 1);
	if (!*value) {
		fclose(ctrl_file);
		last_errno = errno;
		return ECGOTHER;
	}


	ret = fread(*value, 1, CG_VALUE_MAX-1, ctrl_file);
	if (ret < 0) {
		free(*value);
		*value = NULL;
	} else {

		if (ret > 0 && (*value)[ret-1] == '\n')
			(*value)[ret-1] = '\0';
	}

	fclose(ctrl_file);

	return 0;
}
