value_create_range_str( int *val_int, char **names, int count )
{
    int i;
    Value *value = value_create_basic( VALUE_RANGE_STR, val_int );
    value->min = 0; value->max = count - 1; value->step = 1;

    value->name_count = count;
    value->names = calloc( count, sizeof( char* ) );
    for ( i = 0; i < count; i++ )
        value->names[i] = strdup( names[i] );
    value_update_str( value );
    return value;
}
