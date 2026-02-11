display_controller_data(
		char controller[CG_CONTROLLER_MAX][FILENAME_MAX],
		const char *program_name)
{
	int ret;
	void *handle;
	int first = 1;

	struct cgroup_file_info info;
	int lvl;

	int prefix_len;
	char cgroup_name[FILENAME_MAX];

	struct cgroup *group = NULL;


	ret = cgroup_walk_tree_begin(controller[0], "/", 0,
		&handle, &info, &lvl);
	if (ret != 0)
		return ret;

	prefix_len = strlen(info.full_path);


	while ((ret = cgroup_walk_tree_next(0, &handle, &info, lvl)) == 0) {

		if (info.type == CGROUP_FILE_TYPE_DIR) {

			strncpy(cgroup_name, &info.full_path[prefix_len],
				FILENAME_MAX);
			cgroup_name[FILENAME_MAX-1] = '\0';


			group = cgroup_new_cgroup(cgroup_name);
			if (group == NULL) {
				printf("cannot create group '%s'\n",
					cgroup_name);
				ret = ECGFAIL;
				goto err;
			}

			ret = cgroup_get_cgroup(group);
			if (ret != 0) {
				printf("cannot read group '%s': %s\n",
				cgroup_name, cgroup_strerror(ret));
				goto err;
			}

			display_cgroup_data(group, controller, info.full_path,
				prefix_len, first, program_name);
			first = 0;
			cgroup_free(&group);
		}
	}

err:
	cgroup_walk_tree_end(&handle);
	if (ret == ECGEOF)
		ret = 0;

	return ret;

}
