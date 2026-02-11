bibl_malloc( bibl * b )
{
	int alloc = 50;
	b->nrefs = 0;
	b->ref = ( fields ** ) malloc( sizeof( fields* ) * alloc );
	if ( b->ref ) {
		b->maxrefs = alloc;
	} else {
		fprintf( stderr, "bibl_malloc: allocation error\n" );
		exit( EXIT_FAILURE );
	}
}
