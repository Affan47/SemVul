cson_value_is_builtin( void const * m )
{
    if((m >= (void const *)&CSON_EMPTY_HOLDER)
        && ( m < (void const *)(&CSON_EMPTY_HOLDER+1)))
        return 1;
    else return
        ((m >= (void const *)&CSON_SPECIAL_VALUES[0])
        && ( m < (void const *)&CSON_SPECIAL_VALUES[CSON_INTERNAL_VALUES_LENGTH]) )
        ? 1
        : 0;
}
