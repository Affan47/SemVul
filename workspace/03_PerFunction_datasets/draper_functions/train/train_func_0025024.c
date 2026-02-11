class_module_stat( struct hashstats * stats, OBJECT * module, const char * name )
{
    if ( stats->item_size )
    {
        string id[ 1 ];
        string_new( id );
        string_append( id, object_str( module ) );
        string_append( id, " object " );
        string_append( id, name );

        hashstats_print( stats, id->value );

        string_free( id );
    }
}
