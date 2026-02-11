cf_access(char *filename, int dir_type, int mode)
{
	char longname[MAX_PATH_LEN];

	Assert( CF_TYPE_SPECIFIED(dir_type) );

	cf_create_default_path_string( longname, sizeof(longname)-1, dir_type, filename );

	return access(longname,mode);
}
