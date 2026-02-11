remove_xattr(int xmlMode, char *path, char *xattrname)
{
	gfarm_error_t e;

	if (xmlMode) {
		e = gfs_removexmlattr(path, xattrname);
	} else {
		e = gfs_removexattr(path, xattrname);
	}
	return (e);
}
