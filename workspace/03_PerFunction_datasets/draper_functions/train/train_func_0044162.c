InitTree( ChewingData *pgdata, const char * prefix )
{
#ifdef USE_BINARY_DATA
	char filename[ PATH_MAX ];
	size_t len;
	size_t offset;

	len = snprintf( filename, sizeof( filename ), "%s" PLAT_SEPARATOR "%s", prefix, PHONE_TREE_FILE );
	if ( len + 1 > sizeof( filename ) )
		return -1;

	plat_mmap_set_invalid( &pgdata->static_data.tree_mmap );
	pgdata->static_data.tree_size = plat_mmap_create( &pgdata->static_data.tree_mmap, filename, FLAG_ATTRIBUTE_READ );
	if ( pgdata->static_data.tree_size <= 0 )
		return -1;

	offset = 0;
	pgdata->static_data.tree = (TreeType *) plat_mmap_set_view( &pgdata->static_data.tree_mmap, &offset, &pgdata->static_data.tree_size );
	if ( !pgdata->static_data.tree )
		return -1;

	return 0;
#else
	char filename[ PATH_MAX ];
	int len;
	FILE *infile = NULL;
	int i;

	len = snprintf( filename, sizeof( filename ), "%s" PLAT_SEPARATOR "%s", prefix, PHONE_TREE_FILE );
	if ( len + 1 > sizeof( filename ) )
		return -1;

	infile = fopen( filename, "r" );
	if ( !infile )
		return -1;

	pgdata->static_data.tree = ALC( TreeType, TREE_SIZE );
	if ( !pgdata->static_data.tree ) {
		fclose( infile );
		return -1;
	}


	for ( i = 0; i < TREE_SIZE; i++ ) {
		if ( fscanf( infile, "%hu%d%d%d",
					&pgdata->static_data.tree[ i ].phone_id,
					&pgdata->static_data.tree[ i ].phrase_id,
					&pgdata->static_data.tree[ i ].child_begin,
					&pgdata->static_data.tree[ i ].child_end ) != 4 )
			break;
	}

	fclose( infile );
	return 0;
#endif
}
