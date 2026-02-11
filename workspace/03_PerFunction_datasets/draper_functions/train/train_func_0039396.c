testperm(struct stat *stat, int perm) {
	int mask;
	static int uid, gid;
	static Boolean initialized = FALSE;
	if (perm == 0)
		return 0;
	if (!initialized) {
		initialized = TRUE;
		uid = geteuid();
		gid = getegid();
	}
	mask = (uid == 0)
		? (perm << USER) | (perm << GROUP) | (perm << OTHER)
		: (perm <<
			((uid == stat->st_uid)
				? USER
				: ((gid == stat->st_gid  || ingroupset(stat->st_gid))
					? GROUP
					: OTHER)));
	return (stat->st_mode & mask) ? 0 : EACCES;
}
