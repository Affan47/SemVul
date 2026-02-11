flps_set_object_shortcut( FL_OBJECT  * obj,
                          const char * sstr,
                          int          showit )
{
    long sc[ 16 ];
    int scsize, n;

    if ( obj == NULL )
    {
        fprintf( stderr, "fl_set_object_shortcut:Object is NULL\n" );
        return;
    }

    if ( ! sstr || ! *sstr )
        return;

    n = fl_convert_shortcut( sstr, sc );

    scsize = ( n + 1 ) * sizeof *obj->shortcut;
    obj->shortcut = realloc( obj->shortcut, scsize );
    memcpy( obj->shortcut, sc, scsize );

    if ( ! showit || ! obj->label || ! *obj->label || *obj->label == '@' )
        return;

    if (    ( n = fl_get_underline_pos( obj->label, sstr ) ) > 0
         && ! strchr( obj->label, *ul_magic_char ) )
    {
        char *q = obj->label;

        obj->label = malloc( strlen( q ) + 2 );
        strncpy( obj->label, q, n );
        obj->label[ n ] = *ul_magic_char;
        strcpy( obj->label + n + 1, q + n );
        free( q );
    }
}
