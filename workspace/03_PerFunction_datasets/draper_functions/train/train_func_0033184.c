var_parse_actions_free( VAR_PARSE_ACTIONS * actions )
{
    int i;
    for ( i = 0; i < actions->elems->size; ++i )
    {
        var_parse_group_free( dynamic_array_at( VAR_PARSE_GROUP *, actions->elems, i ) );
    }
    dynamic_array_free( actions->elems );
    BJAM_FREE( actions );
}
