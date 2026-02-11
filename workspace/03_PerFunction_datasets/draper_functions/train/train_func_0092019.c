loadfile( const char * file,
          void       * data  FL_UNUSED_ARG )
{
    char buf[ 512 ];
    char *cwd = fli_getcwd( buf, sizeof buf - 2 );
    const char *s = strstr( file, cwd );

    if ( ! s )
        s = file;
    else
        s = file + strlen( cwd ) + 1;

    fl_set_input( px_attrib->filename, s );
    fl_call_object_callback( px_attrib->filename );
    return 1;
}
