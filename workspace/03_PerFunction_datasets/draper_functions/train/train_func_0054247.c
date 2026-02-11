ff_match_uint( unsigned int * p )
{
    unsigned long val;
    char *old_pos = ff.pos;

    if ( ff_match_ulong( &val ) < 0 )
        return -1;

    if ( val > UINT_MAX )
    {
        ff.pos = old_pos;
        return -1;
    }

    *p = val;
    return 0;
}
