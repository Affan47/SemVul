ff_match_unit( int * p )
{
    char *unit_name;
    char *old_pos = ff.pos;
    int unit;

    if ( ff_match_spaceless_string( &unit_name ) < 0 )
        return -1;

    if ( ! *unit_name || ( unit = unit_val( unit_name ) ) == -1 )
    {
        ff.pos = old_pos;
        fl_safe_free( unit_name );
        return -1;
    }

    *p = unit;
    fl_safe_free( unit_name );
    return 0;
}
