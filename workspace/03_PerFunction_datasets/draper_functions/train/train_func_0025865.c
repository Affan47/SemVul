shared_lock( int fd, const char *path )
{
	int wait_msg = 0;
	struct flock lk;


	lk.l_type = F_RDLCK;
	lk.l_start = 0;
	lk.l_whence = SEEK_SET;
	lk.l_len = 0;

	while( fcntl( fd, F_SETLK, &lk ) == -1 )
	{
		if( errno == EAGAIN || errno == EACCES )
		{
			if( ! wait_msg++ )
				msglog( MSG_NOTICE, "waiting for lock file: %s",
							 path );
			if( ! lockfile_sleep( 3 ) )
				return 0;
			continue;
		}
		msglog( MSG_ERR|LOG_ERRNO, "fcntl F_SETLK" );
		return 0;
	}
	return 1;
}
