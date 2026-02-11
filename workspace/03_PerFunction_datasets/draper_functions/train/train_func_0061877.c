us_webapp_fs_validate_path( const char *path )
{
    bool r = true;
    bool last_was_dot = false;
    int i;
    int len = (int)strlen( path );
    for ( i = 0; i < len; ++i )
    {
        char c = path[i];
        if ( c == '.' && last_was_dot )
        {
            r = false;
            break;
        }
        if ( c == '.' )
        {
            last_was_dot = true;
        }
        else
        {
            last_was_dot = false;
        }
        if ( !isprint( c ) || ( c & 0x80 ) != 0 )
        {
            r = false;
            break;
        }
    }
    return r;
}
