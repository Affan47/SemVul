pine_close_file( PineFile *pineFile ) {
	cm_return_if_fail( pineFile != NULL );
	if( pineFile->file ) fclose( pineFile->file );
	pineFile->file = NULL;
}
