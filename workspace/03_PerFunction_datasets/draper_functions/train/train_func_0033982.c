backup_waitpid(pid_t pid, const char *name, int block)
{
	int status;
	int options = block ? 0 : WNOHANG;
	int wrv;

again:
	wrv = waitpid( pid, &status, options );
	if( wrv == -1 && errno == EINTR )
	{
		msglog( MSG_ERR, "waitpid: EINTR received. trying again...");
		sleep( 1 );
		goto again;
	}

	if( wrv == -1 )
	{
		msglog( MSG_ERR|LOG_ERRNO, "waitpid %ld for %s",
							(long) pid, name );
		return 1;
	}
 	else if( ! wrv )
	{
		return 0;
	}
	else if( wrv > 0 )
	{
		if( WIFEXITED( status ) )
		{
			msglog( MSG_INFO,
				"backup process %ld for %s exited with %d",
				(long) pid, name, WEXITSTATUS( status ) );
		}
		else if( WIFSIGNALED( status ) )
		{
			msglog( MSG_INFO, "backup process %ld for %s " \
					"caught signal %d", (long) pid,
					name, WTERMSIG( status ) );
		}
		else
		{

			msglog( MSG_NOTICE,
				"backup process %ld for %s stopped",
					(long) pid, name );
			goto again;
		}
	}
	return 1;
}
