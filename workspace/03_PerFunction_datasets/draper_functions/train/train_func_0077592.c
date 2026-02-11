bson_print_raw( const char * data , int depth ){
    bson_iterator i;
    const char * key;
    int temp;
    char oidhex[25];
    bson_iterator_init( &i , data );

    while ( bson_iterator_next( &i ) ){
        bson_type t = bson_iterator_type( &i );
        if ( t == 0 )
            break;
        key = bson_iterator_key( &i );

        for ( temp=0; temp<=depth; temp++ )
            printf( "\t" );
        printf( "%s : %d \t " , key , t );
        switch ( t ){
        case bson_int: printf( "%d" , bson_iterator_int( &i ) ); break;
        case bson_double: printf( "%f" , bson_iterator_double( &i ) ); break;
        case bson_bool: printf( "%s" , bson_iterator_bool( &i ) ? "true" : "false" ); break;
        case bson_string: printf( "%s" , bson_iterator_string( &i ) ); break;
        case bson_null: printf( "null" ); break;
        case bson_oid: bson_oid_to_string(bson_iterator_oid(&i), oidhex); printf( "%s" , oidhex ); break;
        case bson_object:
        case bson_array:
            printf( "\n" );
            bson_print_raw( bson_iterator_value( &i ) , depth + 1 );
            break;
        default:
            fprintf( stderr , "can't print type : %d\n" , t );
        }
        printf( "\n" );
    }
}
