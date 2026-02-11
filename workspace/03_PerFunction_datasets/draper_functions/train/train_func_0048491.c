access( pfs_name *name, mode_t mode )
{
	if( mode&X_OK ) {
		errno = EACCES;
		return -1;
	} else if( mode&W_OK ) {
		errno = EACCES;
		return -1;
	} else {
		return 0;
	}
}
