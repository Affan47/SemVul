bson_iterator_subobject_init( const bson_iterator *i, bson *sub, bson_bool_t copyData ) {
    const char *data = bson_iterator_value( i );
    if( copyData )
        bson_init_finished_data_with_copy( sub, data );
    else
        bson_init_finished_data( sub, (char *)data, 0 );
}
