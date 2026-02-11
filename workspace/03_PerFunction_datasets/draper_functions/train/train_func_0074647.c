get_arg( FILE *file, char *name, int type )
{
    char token[MAX_TOKEN_LENGTH];
    char *arg = 0;


    if ( !find_token( file, name, type, WARNING ) ) return 0;


    read_token( file, token );

    read_token( file, token );
    if ( token[0] != '=' ) {
        fprintf( stderr,
                 "get_arg: line %i: '=' expected after token '%s' but found '%s' instead\n", get_line_number( file ), name, token );
        return 0;
    }

    read_token( file, token );
    if ( token[0] == 0 )
        fprintf( stderr, "get_arg: line %i: warning: argument for '%s' is empty\n", get_line_number( file ), name );
    arg = strdup( token );
#ifdef FILE_DEBUG
    printf( "get_arg: %s = %s\n", name, arg );
#endif
    return arg;
}
