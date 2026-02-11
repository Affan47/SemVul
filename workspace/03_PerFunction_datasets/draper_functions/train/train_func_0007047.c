apply_subscript_and_modifiers( STACK * s, int n )
{
    LIST * const value = stack_top( s );
    LIST * const indices = stack_at( s, 1 );
    LIST * result = L0;
    VAR_EDITS * const edits = (VAR_EDITS *)((LIST * *)stack_get( s ) + 2);
    int const length = list_length( value );
    string buf[ 1 ];
    LISTITER indices_iter = list_begin( indices );
    LISTITER const indices_end = list_end( indices );
    string_new( buf );
    for ( ; indices_iter != indices_end; indices_iter = list_next( indices_iter
        ) )
    {
        LISTITER iter = list_begin( value );
        LISTITER end = list_end( value );
        subscript_t const sub = parse_subscript( object_str( list_item(
            indices_iter ) ) );
        get_iters( sub, &iter, &end, length );
        result = apply_modifiers_impl( result, buf, edits, n, iter, end );
    }
    string_free( buf );
    return result;
}
