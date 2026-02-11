ocfs2_cluster_hangup(const char *group, int grouplen)
{
	BUG_ON(group == NULL);
	BUG_ON(group[grouplen] != '\0');

	ocfs2_leave_group(group);


	ocfs2_stack_driver_put();
}
