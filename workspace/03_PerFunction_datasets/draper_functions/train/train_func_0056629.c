juti_getgrouplist(const char *uname, gid_t agroup, gid_t **groups_res, char*** group_names_res, int *grpcnt)
{
	struct group *grp;
	int bail;
   int ret = 0;
   int maxgroups = 0;
   gid_t *groups = NULL;
   char  **group_names = NULL;
   int ngroups = 0;
   int i = 0;

	setgrent();
	while ((grp = getgrent())) {
      for (bail = 0, i = 0; bail == 0 && i < ngroups; i++) {
			if (groups[i] == grp->gr_gid) {
				bail = 1;
         }
      }
		if (bail) {
			continue;
      }
		if (grp->gr_gid == agroup) {
         if(add_group(grp, &groups, &group_names, &ngroups, &maxgroups) != 0) {
            ret = -1;
            goto error;
         }
         continue;
      }
		for (i = 0; grp->gr_mem[i]; i++) {
			if (strcmp(grp->gr_mem[i], uname) == 0) {
            if(add_group(grp, &groups, &group_names, &ngroups, &maxgroups) != 0) {
               ret = -1;
               goto error;
            }
			}
		}
	}

	endgrent();

error:

   if (ret != 0) {
      if (groups != NULL) {
         free(groups);
      }
      for (i=0; i < ngroups; i++) {
         free(group_names[i]);
      }
      if (group_names != NULL) {
         free(group_names);
      }
   } else {
      *groups_res = groups;
      *group_names_res = group_names;
      *grpcnt = ngroups;
   }

	return ret;
}
