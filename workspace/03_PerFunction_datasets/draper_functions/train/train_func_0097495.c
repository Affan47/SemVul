entry_allocate( void )
{
	Bqueue *tmp;

	if( bcache.count > 0 )
	{
		pthread_mutex_lock( &bcache.lock );
		if( bcache.count <= 0 )
		{
			pthread_mutex_unlock( &bcache.lock );
			goto dalloc;
		}

		tmp = bcache.list;
		bcache.list = bcache.list->next;
		bcache.count--;
		pthread_mutex_unlock( &bcache.lock );

		memset( tmp, 0, sizeof(*tmp) );
		return tmp;
	}

dalloc:
	if( ( tmp = (Bqueue *) malloc( sizeof(Bqueue) ) ) )
		memset( tmp, 0, sizeof(*tmp) );
	return tmp;
}
