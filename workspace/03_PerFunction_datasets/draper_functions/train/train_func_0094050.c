mongo_create_index( mongo *conn, const char *ns, const bson *key, const char *name, int options, int ttl, bson *out ) {
    bson b;
    bson_iterator it;
    char default_name[INDEX_NAME_BUFFER_SIZE] = {'\0'};
    size_t len = 0;
    size_t remaining;
    char idxns[1024];
    char *p = NULL;

    if ( !name ) {
        bson_iterator_init( &it, key );
        while( len < INDEX_NAME_MAX_LENGTH && bson_iterator_next( &it ) ) {
            remaining = INDEX_NAME_MAX_LENGTH - len;
            strncat( default_name, bson_iterator_key( &it ), remaining );
            len = strlen( default_name );
            remaining = INDEX_NAME_MAX_LENGTH - len;
            strncat( default_name, ( bson_iterator_int( &it ) < 0 ) ? "_-1" : "_1", remaining );
            len = strlen( default_name );
        }
    }

    bson_init( &b );
    bson_append_bson( &b, "key", key );
    bson_append_string( &b, "ns", ns );
    bson_append_string( &b, "name", name ? name : default_name );
    if ( options & MONGO_INDEX_UNIQUE )
        bson_append_bool( &b, "unique", 1 );
    if ( options & MONGO_INDEX_DROP_DUPS )
        bson_append_bool( &b, "dropDups", 1 );
    if ( options & MONGO_INDEX_BACKGROUND )
        bson_append_bool( &b, "background", 1 );
    if ( options & MONGO_INDEX_SPARSE )
        bson_append_bool( &b, "sparse", 1 );

    if( ttl > 0 )
        bson_append_int( &b, "expireAfterSeconds", ttl );

    bson_finish( &b );

    strncpy( idxns, ns, 1024-16 );
    p = strchr( idxns, '.' );
    if ( !p ) {
	    bson_destroy( &b );
        if( out )
            bson_init_zero(out);
	    return MONGO_ERROR;
    }
    strcpy( p, ".system.indexes" );
    if ( mongo_insert( conn, idxns, &b, NULL ) != MONGO_OK) {
	    bson_destroy( &b );
        if( out )
            bson_init_zero(out);
	    return MONGO_ERROR;
    }
    bson_destroy( &b );

    *strchr( idxns, '.' ) = '\0';
    return mongo_cmd_get_last_error( conn, idxns, out );
}
