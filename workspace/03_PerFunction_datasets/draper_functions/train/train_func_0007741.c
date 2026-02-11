get_task_group_name(ulong group)
{
	ulong cgroup, dentry, name;
	char *dentry_buf, *tmp;
	int len;

	tmp = NULL;
	readmem(group + OFFSET(task_group_css) + OFFSET(cgroup_subsys_state_cgroup),
		KVADDR, &cgroup, sizeof(ulong),
		"task_group css cgroup", FAULT_ON_ERROR);
	if (cgroup == 0)
		return NULL;

	readmem(cgroup + OFFSET(cgroup_dentry), KVADDR, &dentry, sizeof(ulong),
		"cgroup dentry", FAULT_ON_ERROR);
	if (dentry == 0)
		return NULL;

	dentry_buf = GETBUF(SIZE(dentry));
	readmem(dentry, KVADDR, dentry_buf, SIZE(dentry),
		"dentry", FAULT_ON_ERROR);
	len = UINT(dentry_buf + OFFSET(dentry_d_name) + OFFSET(qstr_len));
	tmp = GETBUF(len + 1);
	name = ULONG(dentry_buf + OFFSET(dentry_d_name) + OFFSET(qstr_name));
	readmem(name, KVADDR, tmp, len, "qstr name", FAULT_ON_ERROR);

	FREEBUF(dentry_buf);
	return tmp;
}
