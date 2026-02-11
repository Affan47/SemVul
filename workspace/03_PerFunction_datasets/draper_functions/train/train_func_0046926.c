queue_entry_locate( const char *name, unsigned int hash,
								    int key )
{
	Bqueue *bq;

	bq = BQ.hash[ key ];

	while( bq )
	{
		if( hash == bq->hash &&
				*name == bq->dname[0] &&
				! strcmp( bq->dname, name ) )
			return bq;
		bq = bq->next;
	}
	return NULL;
}
