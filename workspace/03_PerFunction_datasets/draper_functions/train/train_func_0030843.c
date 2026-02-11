levelset_save( LevelSet *set, char *fname )
{
	FILE *file;
	Level *level;
	char path[512];
	int i, j, k;

	if ( set == 0 || set->count == 0 ) return 0;

	snprintf( path, sizeof(path)-1, "%s/%s/lbreakout2-levels/%s",
			(getenv( "HOME" )?getenv( "HOME" ):"."),
			CONFIG_DIR_NAME, (fname[0]=='~')?fname+1:fname );
	if ( ( file = fopen( path, "w" ) ) == 0 ) {
		fprintf( stderr, "couldn't open %s\n", path );
		return 0;
	}

	fprintf( file, "Version: %i.%02i\n",
			set->version, set->update );
	for ( k = 0; k < set->count; k++ ) {
		level = set->levels[k];

		fprintf( file, "Level:\n%s\n%s\nBricks:\n",
				level->author, level->name );
		for ( j = 0; j < EDIT_HEIGHT; j++ ) {
			for ( i = 0; i < EDIT_WIDTH; i++ )
				fprintf( file, "%c", level->bricks[i][j] );
			fprintf( file, "\n" );
		}
		fprintf( file, "Bonus:\n" );
		for ( j = 0; j < EDIT_HEIGHT; j++ ) {
			for ( i = 0; i < EDIT_WIDTH; i++ )
				fprintf( file, "%c", level->extras[i][j] );
			fprintf( file, "\n" );
		}
	}

	fclose( file );
	return 1;
}
