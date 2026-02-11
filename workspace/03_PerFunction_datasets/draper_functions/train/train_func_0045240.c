appledouble_truncate(struct afp_volume * volume, const char * path, int offset)
{

	char * newpath;
	int resource = extra_translate(volume, path, &newpath);
	struct afp_file_info fp;
	int ret;
	int dirid;
	char basename[AFP_MAX_PATH];

	switch(resource) {
		case AFP_META_RESOURCE:

			get_dirid(volume,newpath,basename,&dirid);

			ret=afp_openfork(volume,1,dirid,O_WRONLY,
				basename,&fp);

			ret=ll_zero_file(volume,fp.forkid,0);
			if (ret<0) {
				afp_closefork(volume,fp.forkid);
				remove_opened_fork(volume,fp);
				free(newpath);
				return ret;
			}
			afp_closefork(volume,fp.forkid);
			remove_opened_fork(volume,fp);

			return 1;
		case AFP_META_APPLEDOUBLE:
			free(newpath);
			return -EISDIR;
		case AFP_META_FINDERINFO:
			free(newpath);
			return 1;
		case AFP_META_COMMENT:
			free(newpath);
			return 1;
		case AFP_META_SERVER_ICON:
			free(newpath);
			return -EPERM;
	}
	return 0;
}
