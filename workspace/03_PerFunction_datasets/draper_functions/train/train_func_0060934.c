gfarm_ldap_group_info_set_field(
	void *vinfo,
	char *attribute,
	char **vals)
{
	gfarm_error_t err = GFARM_ERR_NO_ERROR;
	struct gfarm_group_info *info = vinfo;
	static const char diag[] = "gfarm_ldap_group_info_set_field";

	if (strcasecmp(attribute, "groupname") == 0) {
		info->groupname = strdup_log(vals[0], diag);
		if (info->groupname == NULL)
			err = GFARM_ERR_NO_MEMORY;
	} else if (strcasecmp(attribute, "groupusers") == 0) {
		info->usernames = gfarm_strarray_dup_log(vals, diag);
		if (info->usernames == NULL) {
			info->nusers = 0;
			err = GFARM_ERR_NO_MEMORY;
		} else {
			info->nusers = gfarm_strarray_length(info->usernames);
		}
	}
	return (err);
}
