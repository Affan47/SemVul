FS_Restart( void )
{
	searchpath_t *path, *next;
	fsFile_t	*file;
	int			i;

	Com_Printf( "---------- FS_Restart ----------\n" );


	for( i = 0, file = fs_files; i < MAX_FILE_HANDLES; i++, file++ ) {
		if( file->type == FS_FREE ) {
			continue;
		}
		if( file->mode == FS_MODE_READ ) {
			Com_Error( ERR_FATAL, "FS_Restart: closing handle %i: %s", i + 1, file->fullpath );
		}
	}


	for( path = fs_searchpaths; path != fs_base_searchpaths; path = next ) {
		next = path->next;
		FS_FreeSearchPath( path );
	}

	fs_searchpaths = fs_base_searchpaths;

	FS_SetupGamedir();

	Com_Printf( "--------------------------------\n" );
}
