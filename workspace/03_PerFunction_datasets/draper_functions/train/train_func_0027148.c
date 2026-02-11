bson_destroy( bson * b ){
    if ( b->owned && b->data )
        free( b->data );
    b->data = 0;
    b->owned = 0;
}
