read_nodes(struct lscpu_desc *desc)
{
	int i = 0;
	DIR *dir;
	struct dirent *d;
	char *path;


	path = path_strdup(_PATH_SYS_NODE);
	dir = opendir(path);
	free(path);

	while (dir && (d = readdir(dir))) {
		if (is_node_dirent(d))
		       desc->nnodes++;
		}

	if (!desc->nnodes) {
		if (dir)
		       closedir(dir);
		return;
	}

	desc->nodemaps = xcalloc(desc->nnodes, sizeof(cpu_set_t *));
	desc->idx2nodenum = xmalloc(desc->nnodes * sizeof(int));

	if (dir) {
		rewinddir(dir);
		while ((d = readdir(dir)) && i < desc->nnodes) {
			if (is_node_dirent(d))
				desc->idx2nodenum[i++] = strtol_or_err(((d->d_name) + 4),
							_("Failed to extract the node number"));
		}
		closedir(dir);
	}


	for (i = 0; i < desc->nnodes; i++)
		desc->nodemaps[i] = path_cpuset(
					_PATH_SYS_SYSTEM "/node/node%d/cpumap",
					desc->idx2nodenum[i]);
}
