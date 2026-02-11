read_stats(char *path, char *controller)
{
	int ret;
	void *handle;
	struct cgroup_stat stat;

	ret = cgroup_read_stats_begin(controller, path,  &handle, &stat);

	if (ret != 0) {
		fprintf(stderr, "stats read failed\n");
		return -1;
	}

	printf("Stats for %s:\n", path);
	printf("%s: %s", stat.name, stat.value);

	while ((ret = cgroup_read_stats_next(&handle, &stat)) !=
			ECGEOF) {
		printf("%s: %s", stat.name, stat.value);
	}

	cgroup_read_stats_end(&handle);
	printf("\n");
	return 0;
}
