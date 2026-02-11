cgroup_get_all_controller_end(void **handle)
{
	FILE *proc_cgroup = (FILE *) *handle;

	if (!proc_cgroup)
		return ECGINVAL;

	fclose(proc_cgroup);
	*handle = NULL;

	return 0;
}
