load_levelsets( void )
{
    DIR *hdir;
    struct dirent *dirent;

    list_clear( levelsets );

    hdir = opendir( SRC_DIR "/levels" );
    if ( hdir == 0 ) {
        printf( _("couldn't open directory %s!\n"), SRC_DIR "/levels" );
        return 0;
    }

    while ( (dirent = readdir( hdir )) ) {
        if ( dirent->d_name[0] == '.' ) continue;
        if ( dirent->d_name[0] != 'N' || dirent->d_name[1] != '_' ) continue;
        list_add( levelsets, levelset_load( dirent->d_name, 0 ) );
    }
    printf( _("loaded %i levelsets from directory %s\n"),
        levelsets->count, SRC_DIR "/levels" );

    closedir( hdir );
    return 1;
}
