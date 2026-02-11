expire_start( int time_out, int ioctlfd, int *shutdown )
{
  	int i;

	expire.stop = 0;
	expire.cur = 1;
	expire.ioctlfd = ioctlfd;
        expire.shutdown = shutdown;
        thread_mutex_init(&expire.lock);

	if( ! time_out )
		return;

	for( i = 0; i < EXPIRE_MAX_THREADS; i++ )
		expire.threads[ i ] = 0;


	if( ! thread_new_joinable( main_expire_mounts, NULL, &expire.main ) )
		msglog( MSG_FATAL, "could not start expire thread" );
}
