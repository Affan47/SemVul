file_dirscan(
	const char *dir,
	scanback func,
	void *closure )
{
	PATHNAME f;
	DIR *d;
	STRUCT_DIRENT *dirent;
	char filename[ MAXJPATH ];


	memset( (char *)&f, '\0', sizeof( f ) );

	f.f_dir.ptr = dir;
	f.f_dir.len = strlen(dir);

	dir = *dir ? dir : ".";


	if( f.f_dir.len == 1 && f.f_dir.ptr[0] == '/' )
	    (*func)( closure, dir, 0 , (time_t)0 );


	if( !( d = opendir( dir ) ) )
	    return;

	if( DEBUG_BINDSCAN )
	    printf( "scan directory %s\n", dir );

	while( dirent = readdir( d ) )
	{
# ifdef old_sinix

	    f.f_base.ptr = dirent->d_name - 2;
# else
	    f.f_base.ptr = dirent->d_name;
# endif
	    f.f_base.len = strlen( f.f_base.ptr );

	    path_build( &f, filename, 0 );

	    (*func)( closure, filename, 0 , (time_t)0 );
	}

	closedir( d );
}
