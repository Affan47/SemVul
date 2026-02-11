pine_read_file( PineFile *pineFile, AddressCache *cache ) {
	GSList *listValue = NULL;
	gboolean flagEOF = FALSE, flagProc = FALSE, flagDone = FALSE;
	gchar *line =  NULL, *lineValue = NULL;
	long posEnd = 0L;
	long posCur = 0L;


	fseek( pineFile->file, 0L, SEEK_END );
	posEnd = ftell( pineFile->file );
	fseek( pineFile->file, 0L, SEEK_SET );

	flagProc = FALSE;
	while( ! flagDone ) {
		if( flagEOF ) {
			flagDone = TRUE;
			flagProc = TRUE;
		}
		else {
			line =  pine_read_line( pineFile );
		}

		posCur = ftell( pineFile->file );
		if( pineFile->cbProgress ) {

			( pineFile->cbProgress ) ( pineFile, & posEnd, & posCur );
		}


		if( line == NULL ) {
			flagEOF = TRUE;
		}
		else {

			if( *line == ' ' ) {
				g_strchug( line );
				listValue = g_slist_append(
						listValue, g_strdup( line ) );
				flagProc = FALSE;
			}
			else {
				flagProc = TRUE;
			}
		}

		if( flagProc ) {
			if( listValue != NULL ) {

				lineValue = mgu_list_coalesce( listValue );
				if( lineValue ) {
					pine_build_items(
						pineFile, cache, lineValue );
				}
				g_free( lineValue );
				lineValue = NULL;
				mgu_free_list( listValue );
				listValue = NULL;
			}
			if( line != NULL ) {

				listValue = g_slist_append(
						listValue, g_strdup( line ) );
			}
		}

		g_free( line );
		line = NULL;
	}


	mgu_free_list( listValue );
	listValue = NULL;
}
