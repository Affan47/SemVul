umount_dir( char *path )
{
	struct stat st;

	if( lstat( path, &st ) )
	{
		if( errno == ENOENT )
			return UMOUNT_SUCCESS;
		msglog( MSG_ERR|LOG_ERRNO, "umount_dir: lstat %s", path );
		return UMOUNT_ERROR;
	}
	if( ! S_ISDIR( st.st_mode ) )
	{
		msglog( MSG_ALERT, "umount_dir: not directory: %s", path );
		return UMOUNT_ERROR;
	}
	if( st.st_dev != autodir.dev )
	{
		if( umount( path ) )
		{
			msglog( MSG_NOTICE|LOG_ERRNO, "umount %s", path );

			if( errno == EBUSY )
				return UMOUNT_NOCHANGE;
		}
	}
	if( rmdir( path ) )
	{
		msglog( MSG_ERR|LOG_ERRNO, "umount_dir: rmdir %s", path );
		return UMOUNT_ERROR;
	}
	return UMOUNT_SUCCESS;
}
