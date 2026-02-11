GetInt( PLIST *list, PNAME name, int *value, int code )
{
        if ( code < 0 ) return( code );
        return( param_write_int( list, name, value ) );
}
