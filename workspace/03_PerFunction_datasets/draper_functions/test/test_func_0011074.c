getallgroups(uid_t uid, gid_t *gid_list, int *size_ptr)
{
	struct passwd *pw;
	if ((pw = getpwuid(uid)) == NULL)
		return "getpwuid failed";

	if (getgrouplist(pw->pw_name, pw->pw_gid, gid_list, size_ptr) < 0)
		return "getgrouplist failed";

	if (gid_list[0] != pw->pw_gid) {
		int j;
		for (j = 0; j < *size_ptr; j++) {
			if (gid_list[j] == pw->pw_gid) {
				gid_list[j] = gid_list[0];
				gid_list[0] = pw->pw_gid;
				break;
			}
		}
	}
	return NULL;
}
