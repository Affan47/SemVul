backup_signal_all( void )
{
	int i;
	Backup_pid *bp, **dptr;

	pthread_mutex_lock( &hash_lock );
	for( i = 0; i < hash_size; i++ )
	{
		for( dptr = &hash[ i ]; *dptr; )
		{
			bp = *dptr;
			dptr = &bp->next;
			pthread_mutex_lock( &bp->lock );
			if( bp->pid > 0 )
				backup_soft_signal( bp->pid );
			pthread_mutex_unlock( &bp->lock );
		}
	}
	pthread_mutex_unlock( &hash_lock );
}
