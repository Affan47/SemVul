parse_var_string( char const * first, char const * last,
    struct dynamic_array * out )
{
    char const * saved = first;
    while ( first != last )
    {

        while ( first != last && isspace( *first ) ) ++first;
        if ( saved != first )
        {
            VAR_PARSE_GROUP * const group = var_parse_group_new();
            var_parse_group_maybe_add_constant( group, saved, first );
            saved = first;
            dynamic_array_push( out, group );
        }
        if ( first == last ) break;


        {
            VAR_PARSE_GROUP * group = var_parse_group_new();
            for ( ; ; )
            {
                if ( first == last || isspace( *first ) )
                {
                    var_parse_group_maybe_add_constant( group, saved, first );
                    saved = first;
                    break;
                }
                if ( try_parse_variable( &first, &saved, group ) )
                    assert( first <= last );
                else
                    ++first;
            }
            dynamic_array_push( out, group );
        }
    }
}
