mount_autodir( char *path, pid_t pgrp,
		pid_t pid, int minp, int maxp)
{
	int pipefd[ 2 ];
	char options[ 128 ];
	char our_name[ 128 ];
	char dot_path[ PATH_MAX+1 ];
	struct stat st;

	if( pipe( pipefd ) < 0 )
		msglog( MSG_FATAL|LOG_ERRNO, "mount_autodir: pipe" );

	snprintf( options, sizeof(options),
		"fd=%d,pgrp=%u,minproto=%d,maxproto=%d",
		pipefd[1], (unsigned)pgrp, minp, maxp );

	snprintf( our_name, sizeof(our_name),
		"%s(pid%u)", autodir_name(), (unsigned) pid);

	if( mount( our_name, path, "autofs", MS_MGC_VAL, options ) )
	{
		close( pipefd[ 0 ] );
		close( pipefd[ 1 ] );
		msglog( MSG_FATAL|LOG_ERRNO,
				"incorrect autofs module loaded? mount %s", path );
	}

	autodir.mounted = 1;
	close( pipefd[ 1 ] );
	autodir.k_pipe = pipefd[ 0 ];
	if( fcntl( autodir.k_pipe, F_SETFL, O_NONBLOCK ) )
		msglog( MSG_FATAL|LOG_ERRNO, "mount_autodir: fcntl" );

	snprintf( dot_path, sizeof(dot_path), "%s/.", path );
	autodir.ioctlfd = open( dot_path, O_RDONLY );
	if( autodir.ioctlfd < 0 )
		msglog( MSG_FATAL|LOG_ERRNO, "mount_autodir: open %s", dot_path );

	if( fstat( autodir.ioctlfd, &st ) < 0 )
		msglog( MSG_FATAL|LOG_ERRNO, "mount_autodir: fstat %s", dot_path );

	autodir.dev = st.st_dev;
}
