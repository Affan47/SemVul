appledouble_chown(struct afp_volume * volume, const char * path,
		uid_t uid, gid_t gid)
{
	int resource;
	char * newpath;


	resource = extra_translate(volume, path, &newpath);
	free(newpath);
	if (resource==0) return 0;
	return -EPERM;

}
