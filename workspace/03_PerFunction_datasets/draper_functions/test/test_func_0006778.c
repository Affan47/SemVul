str2list_index( char * list[], int max, const char *str )
{
    int index;
    if( !list || !str ) {
        if( G.verb > 0 ) fprintf(stderr,"** str2list: bad params (%p,%p)\n",
                                 (void *)list, (void *)str);
        return 0;
    }

    for( index = max; index > 0; index-- )
        if( !strcmp(str, list[index]) ) return index;

    return 0;
}
