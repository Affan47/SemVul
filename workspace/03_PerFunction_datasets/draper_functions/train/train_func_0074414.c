getgrouplist_internal(int *ngroups_ptr, const char *user, gid_t gid)
{
	FILE *grfile;
	gid_t *group_list;
	int ngroups;
	struct group group;
	char buff[PWD_BUFFER_SIZE];


	group_list = xmalloc(8 * sizeof(group_list[0]));
	group_list[0] = gid;
	ngroups = 1;

	grfile = fopen_for_read(_PATH_GROUP);
	if (grfile) {
		while (!bb__pgsreader(bb__parsegrent, &group, buff, sizeof(buff), grfile)) {
			char **m;
			assert(group.gr_mem);
			if (group.gr_gid == gid)
				continue;
			for (m = group.gr_mem; *m; m++) {
				if (strcmp(*m, user) != 0)
					continue;
				group_list = xrealloc_vector(group_list,  3, ngroups);
				group_list[ngroups++] = group.gr_gid;
				break;
			}
		}
		fclose(grfile);
	}
	*ngroups_ptr = ngroups;
	return group_list;
}
