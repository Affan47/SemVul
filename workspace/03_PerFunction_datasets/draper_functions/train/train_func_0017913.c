otf_send_file( const char * fname, Net_Msg & msg, const char * op,
                   ck_socket dest )
{
    FILE * fd = NULL;
    struct stat fs;
    string filename;
    vector<string> args;
    char buf[1024];


    if( !extract_args( fname, filename, args ) )
    {

        fprintf( stderr, "[chuck]: malformed filename + argument list...\n" );
        fprintf( stderr, "    -->  '%s'", fname );
        return FALSE;
    }


    strcpy( msg.buffer, fname );


    strcpy( buf, filename.c_str() );
    fd = open_cat_ck( buf );
    if( !fd )
    {
        fprintf( stderr, "[chuck]: cannot open file '%s' for [%s]...\n", filename.c_str(), op );
        return FALSE;
    }

    if( !chuck_parse( (char *)filename.c_str(), fd ) )
    {
        fprintf( stderr, "[chuck]: skipping file '%s' for [%s]...\n", filename.c_str(), op );
        fclose( fd );
        return FALSE;
    }


    memset( &fs, 0, sizeof(fs) );
    stat( buf, &fs );
    fseek( fd, 0, SEEK_SET );


    EM_log( CK_LOG_INFO, "sending TCP file %s, size=%d", filename.c_str(), (t_CKUINT)fs.st_size );
    EM_pushlog();


    msg.param2 = (t_CKUINT)fs.st_size;
    msg.length = 0;
    otf_hton( &msg );

    ck_send( dest, (char *)&msg, sizeof(msg) );


    t_CKUINT left = (t_CKUINT)fs.st_size;
    while( left )
    {

        EM_log( CK_LOG_FINER, "%03d bytes left ... ", left );

        msg.length = left > NET_BUFFER_SIZE ? NET_BUFFER_SIZE : left;

        msg.param3 = fread( msg.buffer, sizeof(char), msg.length, fd );

        if( !msg.param3 )
        {

            fprintf( stderr, "[chuck]: error while reading '%s'...\n", filename.c_str() );

            left = 0;

            msg.param2 = NET_ERROR;
        }
        else
        {

            left -= msg.param3;

            msg.param2 = left;
        }


        EM_log( CK_LOG_FINER, "sending buffer %03d length %03d...", msg.param3, msg.length );

        otf_hton( &msg );
        ck_send( dest, (char *)&msg, sizeof(msg) );
    }


    EM_poplog();


    fclose( fd );

    return TRUE;
}
