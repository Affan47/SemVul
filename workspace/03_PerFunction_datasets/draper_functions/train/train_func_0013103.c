checkExistingFile( const char* tmpfilename, bool forceoverwrite, bool deleteonly ) {


	FILE* tmpfile= fopen( tmpfilename, "rb" );
	if ( NULL != tmpfile ) {

		fclose( tmpfile );

		if ( forceoverwrite || deleteonly ) {

				unlink( tmpfilename );

		} else {

			printf( "ERROR: will not overwrite existing file '%s', abort\n", tmpfilename );
			exit( 1 );
		}
	}
}
