builtin_shell( FRAME * frame, int flags )
{
    LIST   * command = lol_get( frame->args, 0 );
    LIST   * result = L0;
    string   s;
    int      ret;
    char     buffer[ 1024 ];
    FILE   * p = NULL;
    int      exit_status = -1;
    int      exit_status_opt = 0;
    int      no_output_opt = 0;
    int      strip_eol_opt = 0;


    {
        int a = 1;
        LIST * arg = lol_get( frame->args, a );
        while ( !list_empty( arg ) )
        {
            if ( strcmp( "exit-status", object_str( list_front( arg ) ) ) == 0 )
            {
                exit_status_opt = 1;
            }
            else if ( strcmp( "no-output", object_str( list_front( arg ) ) ) == 0 )
            {
                no_output_opt = 1;
            }
            else if ( strcmp("strip-eol", object_str( list_front( arg ) ) ) == 0 )
            {
                strip_eol_opt = 1;
            }
            arg = lol_get( frame->args, ++a );
        }
    }


    fflush( NULL );

    p = popen( object_str( list_front( command ) ), "r" );
    if ( p == NULL )
        return L0;

    string_new( &s );

    while ( ( ret = fread( buffer, sizeof( char ), sizeof( buffer ) - 1, p ) ) > 0 )
    {
        buffer[ret] = 0;
        if ( !no_output_opt )
        {
            if ( strip_eol_opt )
                rtrim(buffer);
            string_append( &s, buffer );
        }
    }

    exit_status = pclose( p );


    result = list_new( object_new( s.value ) );
    string_free( &s );


    if ( exit_status_opt )
    {
        if ( WIFEXITED(exit_status) )
            exit_status = WEXITSTATUS(exit_status);
        else
            exit_status = -1;
        sprintf( buffer, "%d", exit_status );
        result = list_push_back( result, object_new( buffer ) );
    }

    return result;
}
