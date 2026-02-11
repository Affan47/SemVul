exists_in_str_sub( char *tname, str_sub_vocab_t *str_sub_vocab )
{
    bool retval = FALSE;
    str_sub_vocab_t *found = NULL;

    found = lookup_str_sub( tname, str_sub_vocab );
    if ( found != NULL )
    {
        retval = TRUE;
    }
    return ( retval );

}
