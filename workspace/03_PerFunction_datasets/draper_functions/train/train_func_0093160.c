backup_pidmem_allocate( void )
{
	Backup_pid *bp;
	int pids_idx;
	Backup_pids *pids = 0;

	bp = entry_allocate();
	bp->pid = -1;
	thread_mutex_init( &bp->lock );
	thread_cond_init( &bp->wait );

	pthread_mutex_lock( &pid_holder.lock );
	pids = pid_holder.pids1;
	pids_idx = free_slot_get( pids );
	if( pids_idx < 0 ) {
		pthread_mutex_unlock( &pid_holder.lock );
		entry_free( bp );
		return NULL;
	}
	bp->pids = pids;
	bp->pids_idx = pids_idx;
	pids->s[ pids_idx ] = bp;
	pids->count++;
	pthread_mutex_unlock( &pid_holder.lock );

	return bp;
}
