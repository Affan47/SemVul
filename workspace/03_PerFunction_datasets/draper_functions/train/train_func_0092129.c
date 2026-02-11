shell_rmdir (Camera *camera, const char *args) {
	char *xarg;
	int xlen, ret;

	if (*args == ' ')
		args++;


	xarg = strdup(args);
	xlen = strlen(xarg);
	while (xlen > 1) {
		if (xarg[xlen-1] != '/')
			break;
		xarg[xlen-1] = '\0';
		xlen--;
	}
	ret = gp_camera_folder_remove_dir (camera, p->folder, xarg, p->context);
	free (xarg);
	return ret;
}
