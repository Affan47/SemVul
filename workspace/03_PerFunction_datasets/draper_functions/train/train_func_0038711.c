ml_open(struct afp_volume * volume, const char *path, int flags,
	struct afp_file_info **newfp)
{


	struct afp_file_info * fp ;
	int ret, dsi_ret,rc;
	int create_file=0;
	char resource=0;
	unsigned int dirid;
	char converted_path[AFP_MAX_PATH];
	unsigned char aflags = AFP_OPENFORK_ALLOWREAD;

	if (convert_path_to_afp(volume->server->path_encoding,
		converted_path,(char *) path,AFP_MAX_PATH))
		return -EINVAL;

	if (invalid_filename(volume->server,converted_path))
		return -ENAMETOOLONG;

	if (volume_is_readonly(volume) &&
		(flags & (O_WRONLY|O_RDWR|O_TRUNC|O_APPEND|O_CREAT)))
		return -EACCES;

	if ((fp=malloc(sizeof(*fp)))==NULL) {
		return -1;
	}
	*newfp=fp;

	memset(fp,0,sizeof(*fp));

	ret=appledouble_open(volume,path,flags,fp);
	if (ret<0) return ret;
	if (ret==1) goto out;


	if (get_dirid(volume,converted_path,fp->basename,&dirid)<0)
		return -ENOENT;

	fp->did=dirid;

	ret=ll_open(volume,converted_path,flags,fp);

	if (ret<0) goto error;


out:
	return 0;

error:
	free(fp);
	return ret;
}
