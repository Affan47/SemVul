value_create_key( int *val_int, int *filter )
{
    int i;
    Value *value = value_create_basic( VALUE_KEY, val_int );

    value->filter = calloc( SDLK_LAST, sizeof( int ) );
    for ( i = 0; i < SDLK_LAST; i++ ) value->filter[i] = filter[i];
    value_update_str( value );

    value->other_keys = list_create( LIST_NO_AUTO_DELETE, LIST_NO_CALLBACK );
    return value;
}
