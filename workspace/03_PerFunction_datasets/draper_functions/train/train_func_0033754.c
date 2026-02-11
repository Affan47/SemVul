change_group_based_on_rule(pid_t pid)
{
	uid_t euid;
	gid_t egid;
	char *procname = NULL;
	int ret = -1;


	if (cgroup_get_uid_gid_from_procfs(pid, &euid, &egid)) {
		fprintf(stderr, "Error in determining euid/egid of"
		" pid %d\n", pid);
		goto out;
	}
	ret = cgroup_get_procname_from_procfs(pid, &procname);
	if (ret) {
		fprintf(stderr, "Error in determining process name of"
		" pid %d\n", pid);
		goto out;
	}


	ret = cgroup_change_cgroup_flags(euid, egid, procname, pid, 0);
	if (ret) {
		fprintf(stderr, "Error: change of cgroup failed for"
		" pid %d: %s\n", pid, cgroup_strerror(ret));
		goto out;
	}
	ret = 0;
out:
	if (procname)
		free(procname);
	return ret;
}
