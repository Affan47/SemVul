get_directory_owner(const char *path, char *owner)
{
	char aclpath[CHIRP_PATH_MAX];
	char tmp[CHIRP_LINE_MAX];
	char *r;
	CHIRP_FILE *file;
	int result;

	sprintf(aclpath, "%s/.__acl", path);

	file = cfs_fopen(aclpath, "r");
	if(!file)
		return -1;

	r = cfs_fgets(tmp, sizeof(tmp), file);
	if(!r)
		return -1;
	result = sscanf(tmp, "%[^ \t\n]", owner);

	cfs_fclose(file);

	if(result == 1) {
		return 0;
	} else {
		return -1;
	}
}
